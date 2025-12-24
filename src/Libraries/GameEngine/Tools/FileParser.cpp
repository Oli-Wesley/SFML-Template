#include "FileParser.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <SFML/System/Vector2.hpp>

FileParser::FileParser()
{
}

FileParser::FileParser(std::string path)
{
    loadFromFile(path);
}

bool FileParser::loadFromFile(std::string path)
{
	// attempt to open a file. 
	std::ifstream file(path);
	if (!file.is_open()) return false;
	std::string current_line;
	while (std::getline(file, current_line)) {
		// remove any whitespace on start or end and continue to the next line if its empty. 
		trimString(current_line);
		if (current_line.empty()) continue;

		size_t pos = current_line.find(":");

		// if seperation not found
		if (pos == std::string::npos) continue;

		std::string key = current_line.substr(0, pos);
		std::string value = current_line.substr(pos + 1);

		trimString(key);
		trimString(value);

		data[key] = value;
	}
    file.close();
	return true;
}

// removes whitespace at the beggining and end of a line (thanks internet)
void FileParser::trimString(std::string& s)
{
	s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char c) { return !std::isspace(c); }));
	s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char c) { return !std::isspace(c); }).base(), s.end());
}

void FileParser::lowerString(std::string& s)
{
    for (char& x : s) {
        x = tolower(x);
    }
}



// Specific type returns.
template<>
const int FileParser::getValue<int> (const std::string& key, int defaultValue)
{
    if (!data.count(key)) return defaultValue;
    return std::stoi(data.at(key));
}

template<>
const bool FileParser::getValue<bool>(const std::string& key, bool defaultValue)
{
    if (!data.count(key)) return defaultValue;
    std::string s = data.at(key);
    lowerString(s);
    return s == "true" || s == "1";
}

template<>
const float FileParser::getValue<float>(const std::string& key, float defaultValue)
{
    if (!data.count(key)) return defaultValue;
    return std::stof(data.at(key));
}

template<>
const std::string FileParser::getValue<std::string>(const std::string& key, std::string defaultValue)
{
    if (!data.count(key)) return defaultValue;
    return data.at(key);
}

template<>
const sf::Vector2i FileParser::getValue<sf::Vector2i>(const std::string& key, sf::Vector2i defaultValue)
{
    if (!data.count(key)) return defaultValue;

    std::stringstream ss(data.at(key));
    int x, y;
    char comma;

    if (ss >> x >> comma >> y)
        return { x, y };

    return defaultValue;
}

template<>
const sf::Vector2f FileParser::getValue<sf::Vector2f>(const std::string& key, sf::Vector2f defaultValue)
{
    if (!data.count(key)) return defaultValue;

    std::stringstream ss(data.at(key));
    float x, y;
    char comma;

    if (ss >> x >> comma >> y)
        return { x, y };

    return defaultValue;
}