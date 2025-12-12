#pragma once
#include <string>
#include <vector>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Sound.hpp>
#include <memory>


class AudioSystem {
public:
	static AudioSystem* get();

	static bool playSound(std::string sound_id, int volume);
	static bool playSound(std::string sound_id);
	static void setupPlayers();

protected:
	struct SoundInfo {
		sf::SoundBuffer* buffer;
		int volume;
		std::string id;
	};

	struct PlayerInfo {
		std::unique_ptr<sf::Sound> player;
		std::string id;
		int volume;
	};

	std::vector<SoundInfo> sound_queue;
	std::vector<PlayerInfo> audio_players;
	static AudioSystem* instance;
};
