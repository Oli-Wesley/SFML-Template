#include "AssetDatabase.h"
#include <iostream>
#include <filesystem>
// Define the static member variable
AssetDatabase* AssetDatabase::instance = nullptr;

AssetDatabase* AssetDatabase::get()
{
	if (instance == nullptr)
	{
		instance = new AssetDatabase();
	}
	return instance;
}

sf::Texture* AssetDatabase::getTexture(std::string path)
{
	auto it = textures.find(path);
	if (it != textures.end()) {
		return &it->second;
	}
	return nullptr;
}

sf::SoundBuffer* AssetDatabase::getSound(std::string path)
{
	auto it = sounds.find(path);
	if (it != sounds.end()) {
		return &it->second;
	}
	return nullptr;
}

sf::Font* AssetDatabase::getFont(std::string path)
{
	auto it = fonts.find(path);
	if (it != fonts.end()) {
		return &it->second;
	}
	return nullptr;
}


AssetDatabase::AssetDatabase()
{
	// load all assets from Data/Images, Data/Fonts, Data/Sounds and their sub directories and store as map with the key being the relative path and the value being the asset itself
	loadTextures();
	loadSounds();
	loadFonts();
}

void AssetDatabase::loadTextures()
{
	std::cout << "---------------------------------------------------\n";
	std::cout << "__Loading Textures: " << std::endl;
	std::vector<std::string> all_paths = getAllPathsInDirectory("../Data/Textures");
	std::string accepted_types[2] = { "png", "jpg" }; // array of accepted extensions
	bool correct = false;

	for (std::string path_extension : all_paths)
	{
		correct = false;
		size_t pos = path_extension.find('.');
		std::string path = path_extension.substr(0, pos);
		std::string extension = path_extension.substr(pos + 1);
		for (std::string accepted_extension : accepted_types) {
			if (accepted_extension == extension) {
				sf::Texture tex;
				if (tex.loadFromFile("../Data/Textures/" + path_extension)) {
					correct = true;
					textures.emplace(path, tex);
					std::cout << "Loaded Texture: " << path << std::endl;
				}
				else 
					std::cout << "Failed To Load Texture: " << path_extension << std::endl;
			}
		}
		if (!correct)
			std::cout << "Found File Of Unallowed Extension In Folder: " << path_extension << std::endl;
	}
	std::cout << "---------------------------------------------------\n";
}

void AssetDatabase::loadSounds()
{
	std::cout << "__Loading Sounds__: " << std::endl;
	std::vector<std::string> all_paths = getAllPathsInDirectory("../Data/Sounds");
	std::string accepted_types[2] = { "wav", "ogg" }; // array of accepted extensions
	bool correct = false;

	for (std::string path_extension : all_paths)
	{
		correct = false;
		size_t pos = path_extension.find('.');
		std::string path = path_extension.substr(0, pos);
		std::string extension = path_extension.substr(pos + 1);
		for (std::string accepted_extension : accepted_types) {
			if (accepted_extension == extension) {
				sf::SoundBuffer sound;
				if (sound.loadFromFile("../Data/Sounds/" + path_extension)) {
					correct = true;
					sounds.emplace(path, sound);
					std::cout << "Loaded Sound: " << path << std::endl;
				}
				else
					std::cout << "Failed To Load Sound: " << path_extension << std::endl;
			}
		}
		if (!correct)
			std::cout << "Found File Of Unallowed Extension In Folder: " << path_extension << std::endl;
	}
	std::cout << "---------------------------------------------------\n";
}

void AssetDatabase::loadFonts()
{
	std::cout << "__Loading Fonts__: " << std::endl;
	std::vector<std::string> all_paths = getAllPathsInDirectory("../Data/Fonts");
	std::string accepted_types[1] = { "ttf"}; // array of accepted extensions
	bool correct = false;

	for (std::string path_extension : all_paths)
	{
		correct = false;
		size_t pos = path_extension.find('.');
		std::string path = path_extension.substr(0, pos);
		std::string extension = path_extension.substr(pos + 1);
		for (std::string accepted_extension : accepted_types) {
			if (accepted_extension == extension) {
				
				sf::Font font;
				if (font.loadFromFile("../Data/Fonts/" + path_extension)) {
					correct = true;
					fonts.emplace(path, font);
					std::cout << "Loaded Font: " << path << std::endl;
				}
				else
					std::cout << "Failed To Load Font: " << path_extension << std::endl;
			}
		}
		if (!correct)
			std::cout << "Found File Of Unallowed Extension In Folder: " << path_extension << std::endl;
	}
	std::cout << "---------------------------------------------------\n";
}

std::vector<std::string> AssetDatabase::getAllPathsInDirectory(std::string directory)
{
	std::vector<std::string> all_paths;

	for (const auto& entry : std::filesystem::recursive_directory_iterator(directory)) {
		if (entry.is_regular_file()) {
			std::filesystem::path relative_path = std::filesystem::relative(entry.path(), directory);
			std::string entry_s = relative_path.string();
			std::replace(entry_s.begin(), entry_s.end(), '\\', '/');
			all_paths.push_back(entry_s);
		}
	}
	return all_paths;
}
