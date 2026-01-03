#pragma once
#include <string>
#include <vector>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/Music.hpp>
#include <memory>


class AudioSystem {
public:
	static AudioSystem* get();

	// gives a sound to play at the end of the current frame.
	static bool playSound(const std::string &sound_id, float volume);
	static bool playSound(const std::string &sound_id);
	// Plays Music at the end of the current Frane
	static bool playMusic(const std::string &sound_id, bool loop, float volume);
	static bool playMusic(const std::string &sound_id, bool loop);
	static void setupPlayers();
	static void clearPlayers();

protected:
	struct SoundInfo {
		std::string id;
		float volume = 50;
	};

	struct PlayerInfo {
		std::unique_ptr<sf::Sound> player;
		std::string id;
		float volume = 50;
	};

	struct MusicInfo {
		std::unique_ptr<sf::Music> music;
		std::string id;
		float volume = 50;
	};

	std::vector<SoundInfo> sound_queue;
	std::vector<PlayerInfo> audio_players;
	std::vector<MusicInfo> music;
	static AudioSystem* instance;
};
