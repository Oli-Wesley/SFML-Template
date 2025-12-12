#include "AssetDatabase.h"
#include <filesystem>
#include <iostream>
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
	AssetDatabase* asd = get();

	auto it = asd->textures.find(path);
	if (it != asd->textures.end()) {
		return &it->second;
	}
	return nullptr;
}

sf::SoundBuffer* AssetDatabase::getSound(std::string path)
{
	AssetDatabase* asd = get();
	auto it = asd->sounds.find(path);
	if (it != asd->sounds.end()) {
		return &it->second;
	}
	return nullptr;
}

sf::Font* AssetDatabase::getFont(std::string path)
{
	AssetDatabase* asd = get();
	auto it = asd->fonts.find(path);
	if (it != asd->fonts.end()) {
		return &it->second;
	}
	return nullptr;
}

AssetDatabase::AssetDatabase()
{
	// load all assets from Data/Images, Data/Fonts, Data/Sounds and their sub directories and store as map with the key being the relative path and the value being the asset itself
	loadAssets<sf::Texture>(
		"../Data/Textures",
		{ "png", "jpg" },
		textures,
		"Texture"
	);

	loadAssets<sf::SoundBuffer>(
		"../Data/Sound Effects",
		{ "wav", "ogg" },
		sounds,
		"Sound Effects"
	);

	loadAssets<sf::Font>(
		"../Data/Fonts",
		{ "ttf" },
		fonts,
		"Font"
	);
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

void AssetDatabase::print(std::string string)
{
	std::cout << string;
}
