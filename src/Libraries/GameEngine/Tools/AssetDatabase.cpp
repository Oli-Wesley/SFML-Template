#include "AssetDatabase.h"
#include <filesystem>
#include <iostream>
#include "../Systems/GameSystem.h"
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

const sf::Texture& AssetDatabase::getTexture(std::string path)
{
	AssetDatabase* asd = get();

	auto it = asd->textures.find(path);
	if (it != asd->textures.end()) {
		return it->second;
	}
	std::cout << "Warning: texture file is not found (" << path << ")\n";
	return (getTexture("EngineCore/Missing_Tex"));
}

const sf::SoundBuffer& AssetDatabase::getSound(std::string path)
{
	AssetDatabase* asd = get();
	auto it = asd->sounds.find(path);
	if (it != asd->sounds.end()) {
		return it->second;
	}
	std::cout << "Warning: sound file is not found (" << path << ")\n";
	return getSound("EngineCore/Missing_Sound");
}

const sf::Font& AssetDatabase::getFont(std::string path)
{
	AssetDatabase* asd = get();
	auto it = asd->fonts.find(path);
	if (it != asd->fonts.end()) {
		return it->second;
	}
	std::cout << "Warning: font file is not found (" << path << ")\n";
	return getFont("EngineCore/Comic Sans MS"); 
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
		"../Data/Sounds",
		{ "wav", "ogg" },
		sounds,
		"Sound"
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
	if (GameSystem::get()->isDebug())
		std::cout << string;
}
