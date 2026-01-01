#pragma once
#include <map>
#include <sstream>
#include <string>
#include "ValueNode.h"

class FileParser {
public:
    ValueNode loadFromFile(const std::string &path);
protected:
    std::string file;
    int cursor = 0;
    std::vector<ValueNode*> node_stack;

    // logic for parsing node
    ValueNode parseNode();

    // navigation functions
    char peek() const; // read next character without moving cursor forwards
    char consume(); // get next character and move cursor forwards
    void skipWhitespace(); // move cursor forwards until no more whitespace
    bool isAtEnd() const;

    // reads until reaching the given character.
    std::string readUntil(char char_to_reach);

    static std::string loadStringFromFile(const std::string &path);

    static void trimString(std::string& string_to_trim);

    static void lowerString(std::string& string_to_lower);
};
