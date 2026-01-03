#include "ValueNode.h"

#include <algorithm>
#include <fstream>
#include <sstream>
#include <SFML/System/Vector2.hpp>

ValueNode *ValueNode::findChild(const std::string &type, const std::string &name) {
    for (ValueNode& child : children) {
        if (child.type == type && child.name == name)
            return &child;
    }
    return nullptr; // cant find it :(
}

bool ValueNode::hasData() const {
    return !data.empty();
}

std::string ValueNode::removeCharacters(std::string s, char c) {
    s.erase(std::ranges::remove(s, c).begin(), s.end());
    return s;
}

// Specific type returns.
template<>
int ValueNode::getValue<int>(int defaultValue) const {
    if (data.empty()) return defaultValue;
    try {
        return std::stoi(data);
    } catch (...) { return defaultValue; }
}

template<>
bool ValueNode::getValue<bool>(bool defaultValue) const {
    if (data.empty()) return defaultValue;
    const std::string s = data;
    return (s == "true" || s == "1");
}

template<>
float ValueNode::getValue<float>(float defaultValue) const {
    if (data.empty()) return defaultValue;
    try {
        return std::stof(data);
    } catch (...) { return defaultValue; }
}

template<>
std::string ValueNode::getValue<std::string>(std::string defaultValue) const {
    if (data.empty()) return defaultValue;

    return removeCharacters(data, '"');
}

template<>
char ValueNode::getValue<char>(char defaultValue) const {
    if (data.empty()) return defaultValue;

    for (char c : data) {
        if (c != '\'') return c;  // return first non quote character
    }
    // if cant find the char
    return defaultValue;
}

template<>
sf::Vector2i ValueNode::getValue<sf::Vector2i>(sf::Vector2i defaultValue) const {
    if (data.empty()) return defaultValue;
    std::string data_to_parse = removeCharacters(data, '{');
    data_to_parse = removeCharacters(data_to_parse, '}');
    std::stringstream ss(data_to_parse);
    int x, y;
    char comma;
    if (ss >> x >> comma >> y) return { x, y };
    return defaultValue;
}

template<>
sf::Vector2f ValueNode::getValue<sf::Vector2f>(sf::Vector2f defaultValue) const {
    if (data.empty()) return defaultValue;
    std::string data_to_parse = removeCharacters(data, '{');
    data_to_parse = removeCharacters(data_to_parse, '}');
    std::stringstream ss(data_to_parse);
    float x, y;
    char comma;
    if (ss >> x >> comma >> y) return { x, y };
    return defaultValue;
}