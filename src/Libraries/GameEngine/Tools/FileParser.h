#pragma once
#include <string>
#include <unordered_map>

class FileParser {
public:
	FileParser();
	FileParser(std::string path);;
	// load from filepath (from root, no special folders here).
	bool loadFromFile(std::string path);

	template<typename T>
	const T getValue(const std::string& key, T defaultValue);

protected:
	std::unordered_map<std::string, std::string> data;

	void trimString(std::string& string_to_trim);
	void lowerString(std::string& string_to_lower);
};