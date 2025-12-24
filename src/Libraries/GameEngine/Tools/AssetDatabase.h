#pragma once
#include <functional>
#include <string>
#include <unordered_map>
#include <memory> // Include for std::unique_ptr
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Music.hpp>
#include <SFML/Graphics/Font.hpp>


class AssetDatabase
{
public:
	AssetDatabase();
	// get a pointer to the prefab registry singleton instance
	static AssetDatabase* get();

	// Get Texture from path starting in images folder, with the extension removed.
	static const sf::Texture& getTexture(std::string path);
	// Get SoundBuffer from path starting in images folder, with the extension removed.
	static const sf::SoundBuffer& getSound(std::string path);
	// Get Font from path starting in images folder, with the extension removed.
	static const sf::Font& getFont(std::string path);
protected:
	std::unordered_map<std::string, sf::Texture> textures;
	std::unordered_map<std::string, sf::SoundBuffer> sounds;
	std::unordered_map<std::string, sf::Font> fonts;
	static AssetDatabase* instance;
	AssetDatabase(AssetDatabase const&) = delete;
	void operator=(AssetDatabase const&) = delete;
	std::vector < std::string> getAllPathsInDirectory(std::string directory);
	void print(std::string string);





	// load assets in a single function rather than the 3 different ones I had previously, saves repeated code :D. 
	template <typename T>
	void loadAssets(
		const std::string& folder,
		const std::vector<std::string>& extensions,
		std::unordered_map<std::string, T>& array,
		const std::string& label
	) 
	{
		print("__Loading " + label + "(s)__:\n");

		std::vector<std::string> files = getAllPathsInDirectory(folder);

		for (const std::string& file : files)
		{
			size_t pos = file.find('.');
			std::string name = file.substr(0, pos);
			std::string ext = file.substr(pos + 1);

			bool allowed = false;
			for (const auto& e : extensions)
				if (e == ext)
					allowed = true;

			if (!allowed) {
				print("!!! Unallowed File Found: " + file + "\n");
				continue;
			}

			T asset;
			if (asset.loadFromFile(folder + "/" + file)) {
				array.emplace(name, std::move(asset));
				print("Loaded " + label + ": " + name + "\n");
			}
			else {
				print("!!! Failed To Load " + label + ": " + file + "\n");
			}
		}

		print("---------------------------------------------------\n");
	}

};