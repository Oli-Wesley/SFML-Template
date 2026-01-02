#include "AssetDatabase.h"
#include <filesystem>
#include <iostream>
#include <thread>

#include "../Systems/GameSystem.h"
// Define the static member variable
AssetDatabase *AssetDatabase::instance = nullptr;

AssetDatabase *AssetDatabase::get() {
    if (instance == nullptr) {
        instance = new AssetDatabase();
    }
    return instance;
}

void AssetDatabase::clearAssets() {
    AssetDatabase *asd = get();
    asd->textures.clear();
    asd->fonts.clear();
    asd->animations.clear();
    asd->sounds.clear();
    instance = nullptr; // destroy instance so assets can be re-generated if accidentally destroyed at runtime.
}

const sf::Texture &AssetDatabase::getTexture(const std::string &path) {
    AssetDatabase *asd = get();

    if (auto it = asd->textures.find(path); it != asd->textures.end()) {
        return it->second;
    }
    std::cout << "Warning: texture file is not found (" << path << ")\n";
    return (getTexture("EngineCore/Missing_Tex"));
}

const sf::SoundBuffer &AssetDatabase::getSound(const std::string &path) {
    AssetDatabase *asd = get();
    if (auto it = asd->sounds.find(path); it != asd->sounds.end()) {
        return it->second;
    }
    std::cout << "Warning: sound file is not found (" << path << ")\n";
    return getSound("EngineCore/Missing_Sound");
}

const sf::Font &AssetDatabase::getFont(const std::string &path) {
    AssetDatabase *asd = get();
    if (auto it = asd->fonts.find(path); it != asd->fonts.end()) {
        return it->second;
    }
    std::cout << "Warning: font file is not found (" << path << ")\n";
    return getFont("EngineCore/Comic Sans MS");
}

const Animation &AssetDatabase::getAnimation(const std::string &path) {
    AssetDatabase *asd = get();
    if (const auto it = asd->animations.find(path); it != asd->animations.end()) {
        return it->second;
    }
    std::cout << "Warning: Animation file is not found (" << path << ")\n";
    return getAnimation("EngineCore/Missing_Animation");
}

AssetDatabase::AssetDatabase() {
    // load all assets given path, extensions, array to store to, and a label for outputting to console
    std::thread animation_thread([&] {
        loadAssets<Animation>(
            "../Data/Animations/",
            {"anim"},
            animations,
            "Animation"
        );
    });

    std::thread sound_thread([&] {
        loadAssets<sf::SoundBuffer>(
            "../Data/Sounds",
            {"wav", "ogg"},
            sounds,
            "Sound"
        );
    });

    std::thread font_thread([&] {
        loadAssets<sf::Font>(
            "../Data/Fonts",
            {"ttf"},
            fonts,
            "Font"
        );
    });

    // textures stay on main thread as can't be done elsewhere bc of opengl or smth
    loadAssets<sf::Texture>(
        "../Data/Textures",
        {"png", "jpg"},
        textures,
        "Texture"
    );

    animation_thread.join();
    sound_thread.join();
    font_thread.join();
    print("Loaded All Assets \n");
}

std::vector<std::string> AssetDatabase::getAllPathsInDirectory(const std::string &directory) {
    std::vector<std::string> all_paths;

    for (const auto &entry: std::filesystem::recursive_directory_iterator(directory)) {
        if (entry.is_regular_file()) {
            std::filesystem::path relative_path = std::filesystem::relative(entry.path(), directory);
            std::string entry_s = relative_path.string();
            std::replace(entry_s.begin(), entry_s.end(), '\\', '/');
            all_paths.push_back(entry_s);
        }
    }
    return all_paths;
}

void AssetDatabase::print(std::string string) {
    std::cout << string;
}
