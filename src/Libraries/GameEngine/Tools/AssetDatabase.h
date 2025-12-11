#pragma once
#include <functional>
#include <string>
#include <unordered_map>
#include <memory> // Include for std::unique_ptr
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Graphics/Font.hpp>


class AssetDatabase
{
public:
	// get a pointer to the prefab registry singleton instance
	static AssetDatabase* get();

	// Get Texture from path starting in images folder, with the extension removed.
	sf::Texture* getTexture(std::string path);
	// Get SoundBuffer from path starting in images folder, with the extension removed.
	sf::SoundBuffer* getSound(std::string path);
	// Get Font from path starting in images folder, with the extension removed.
	sf::Font* getFont(std::string path);

protected:
	AssetDatabase();

	static AssetDatabase* instance;
	AssetDatabase(AssetDatabase const&) = delete;
	void operator=(AssetDatabase const&) = delete;
	void loadTextures();
	void loadSounds();
	void loadFonts();
	std::vector < std::string> getAllPathsInDirectory(std::string directory);
	std::unordered_map<std::string, sf::Texture> textures;
	std::unordered_map<std::string, sf::SoundBuffer> sounds;
	std::unordered_map<std::string, sf::Font> fonts;
};