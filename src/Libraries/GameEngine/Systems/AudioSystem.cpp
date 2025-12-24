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
    //setup info and move to sound queue.
    SoundInfo info;
    info.id = sound_id;
    info.volume = volume;
    get()->sound_queue.push_back(std::move(info));
    return true;
}

bool AudioSystem::playSound(std::string sound_id)
{
	return playSound(sound_id, 50); // if no volume given, presume 50;
}

// currently untested
bool AudioSystem::playMusic(std::string sound_id, bool loop, int volume)
{
    std::string music_path = "../Data/Music/";
    MusicInfo music_info;
    if (!music_info.music->openFromFile(music_path + sound_id)) {
        return false;
    }
    
    music_info.music->setLoop(loop);
    music_info.music->play();
    music_info.volume = volume;
    music_info.id = sound_id;
    get()->music.push_back(std::move(music_info));
    return true;
}

bool AudioSystem::playMusic(std::string sound_id, bool loop)
{
    return playMusic(sound_id, loop, 50);
}

// setup players (actually plays the sounds)
void AudioSystem::setupPlayers()
{
    AudioSystem* asy = get();

    for (SoundInfo& sound_info : asy->sound_queue)
    {
        PlayerInfo player_info;
        player_info.player = std::make_unique<sf::Sound>(AssetDatabase::getSound(sound_info.id));
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

    // remove Music Players that have finished Playing.
    for (int i = asy->music.size() - 1; i >= 0; --i)
    {
        if (asy->music[i].music->getStatus() == sf::Sound::Stopped)
        {
            asy->music.erase(asy->music.begin() + i);
        }
    }
}