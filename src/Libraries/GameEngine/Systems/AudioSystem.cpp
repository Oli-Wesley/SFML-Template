#include "AudioSystem.h"
#include "../Tools/AssetDatabase.h"
#include <iostream>

AudioSystem* AudioSystem::instance = nullptr;

AudioSystem* AudioSystem::get()
{
	if (instance == nullptr)
	{
		instance = new AudioSystem();
	}
	return instance;
}

// plays a sound sound id as path without file extension e.g playerSounds/hit
bool AudioSystem::playSound(std::string sound_id, int volume)
{
    AudioSystem* asy = get();

    sf::SoundBuffer* sound = AssetDatabase::getSound(sound_id);
    // if no sound, print and return. 
    if (!sound) {
        std::cout << "Could not play sound: (" << sound_id
            << ") as it does not exist in asset database.\n";
        return false;
    }
    
    //setup info and move to sound queue.
    SoundInfo info;
    info.id = sound_id;
    info.volume = volume;
    info.buffer = sound;
    asy->sound_queue.push_back(std::move(info));
    return true;
}

bool AudioSystem::playSound(std::string sound_id)
{
	return playSound(sound_id, 50); // if no volume given, presume 50;
}

// setup players (actually plays the sounds)
void AudioSystem::setupPlayers()
{
    AudioSystem* asy = get();

    for (SoundInfo& sound_info : asy->sound_queue)
    {
        PlayerInfo player_info;
        player_info.player = std::make_unique<sf::Sound>(*sound_info.buffer);
        player_info.player->setVolume(sound_info.volume);
        player_info.player->play();
        player_info.id = sound_info.id;

        asy->audio_players.push_back(std::move(player_info));
    }

    asy->sound_queue.clear(); // remove all queue entries at once

	// remove players that have finished playing.
    for (int i = asy->audio_players.size() - 1; i >= 0; --i)
    {
        if (asy->audio_players[i].player->getStatus() == sf::Sound::Stopped) 
        {
            asy->audio_players.erase(asy->audio_players.begin() + i);
        }
    }
}


