#include "FileParser.h"

#include <algorithm>
#include <fstream>
#include <sstream>

ValueNode FileParser::loadFromFile(const std::string &path) {
    file = loadStringFromFile(path);
    cursor = 0;
    // parse the first node
    // if file is empty, fail to load
    ValueNode root;
    if (file.empty()) {
        root.type = "EMPTY";
        return root;
    }

    // parse the file.
    root = parseNode();
    // if a name override isn't given, set the value name of the root to the file name
    if (root.name.empty()) {
        size_t lastSlash = path.find_last_of("/\\");
        size_t lastDot = path.find_last_of('.');
        size_t start = (lastSlash == std::string::npos) ? 0 : lastSlash + 1;
        size_t length = (lastDot == std::string::npos || lastDot < start) ? std::string::npos : lastDot - start;
        root.name = path.substr(start, length);
    }
    return root;
}


ValueNode FileParser::parseNode() {
    ValueNode node;
    skipWhitespace();
    // check if a new section
    if (peek() == '[') {
        consume(); // eat the found character.
        // Read until we hit '(' or ']'
        node.type = "";
        while (!isAtEnd() && peek() != '(' && peek() != ']') {
            node.type += consume(); // get value.
        }

        // If there's a name, save it.
        if (peek() == '(') {
            consume(); // value we want
            node.name = readUntil(')');
            consume(); // eat closing ')'.
            skipWhitespace();
        }
        // Eat the closing ']'
        consume();

        // look for start of body '{'
        skipWhitespace();
        if (peek() == '{') {
            consume(); // Eat '{'
            // while it hasn't reached its own closing bracket...
            while (!isAtEnd() && peek() != '}') {
                // step inside and parse this new node.
                node.children.push_back(parseNode());
                skipWhitespace();
            }
            // if it has reached own closing bracket eat it and continue on
            consume(); // Eat '}'
        }
    }
    // isn't a new section, so just save it as a property.
    else {
        // Key(Value)
        node.type = "PROPERTY";
        // read the value name until it reaches the opening bracket where the value is stored.
        node.name = readUntil('(');
        consume(); // Eat '('
        node.data_type = readUntil('|');
        consume(); // eat the colon
        // save the data until it reaches the closing bracket
        node.data = readUntil(')');
        consume(); // Eat ')'
    }

    // remove any whitespace at start or back of data
    trimString(node.type);
    trimString(node.name);
    trimString(node.data);
    return node;
}

char FileParser::peek() const {
    if (isAtEnd()) return '\0';
    return file.at(cursor);
}

char FileParser::consume() {
    if (isAtEnd()) return '\0';
    return file.at(cursor++);
}

void FileParser::skipWhitespace() {
    while (!isAtEnd()) {
        if (std::isspace(peek()))
            consume(); // eat the whitespace
        // if a comment, read until the end of the line
        else if (peek() == '#') {
            readUntil('\n');
        }
        // if not whitespace or a comment, must be something important so stop skipping here.
        else {
            return;
        }
    }
}

bool FileParser::isAtEnd() const {
    return (cursor >= file.size());
}

std::string FileParser::readUntil(const char char_to_reach) {
    std::string return_string;
    // keep saving data to the string until the character is reached.
    while (!isAtEnd() && peek() != char_to_reach) {
        return_string.push_back(consume());
    }
    return return_string;
}

std::string FileParser::loadStringFromFile(const std::string &path) {
    std::ifstream file(path);
    if (!file.is_open()) return ""; // if cant open file return empty.

    std::stringstream buffer;
    buffer << file.rdbuf();
    // dump buffer to string.
    return buffer.str();
}

// removes whitespace at the beginning and end of a line (thanks internet)
void FileParser::trimString(std::string& string_to_trim)
{
    string_to_trim.erase(string_to_trim.begin(), std::ranges::find_if(string_to_trim, [](unsigned char c) { return !std::isspace(c); }));
    string_to_trim.erase(std::ranges::find_if(string_to_trim.rbegin(), string_to_trim.rend(), [](unsigned char c) { return !std::isspace(c); }).base(), string_to_trim.end());
}

// lowers all characters in the string (unused)
void FileParser::lowerString(std::string& string_to_lower) {
    for (char &x: string_to_lower) {
        x = static_cast<char>(tolower(x));
    }
}