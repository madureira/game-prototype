#include "audio_manager.h"

namespace core { namespace audio {

	AudioManager::AudioManager()
	{
		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		{
			printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
		}
	}

	AudioManager::~AudioManager()
	{
		for (auto& music : m_Musics)
		{
			Mix_FreeMusic(music.second);
		}

		for (auto& chunk : m_Chunks)
		{
			Mix_FreeChunk(chunk.second);
		}

		m_Musics.clear();
		m_Chunks.clear();
		Mix_Quit();
	}

	bool AudioManager::load(std::string title, std::string audioFile, SOUND_TYPE type)
	{
		if (type == MUSIC)
		{
			m_Musics[title] = Mix_LoadMUS(audioFile.c_str());
			if (m_Musics[title] == NULL)
			{
				printf("Failed to load music! SDL_mixer Error: %s\n", Mix_GetError());
				return false;
			}
		}
		else if (type == CHUNK)
		{
			m_Chunks[title] = Mix_LoadWAV(audioFile.c_str());
			if (m_Chunks[title] == NULL)
			{
				printf("Failed to load sound effect! SDL_mixer Error: %s\n", Mix_GetError());
				return false;
			}
		}

		return true;
	}

	void AudioManager::play(std::string title, SOUND_TYPE type)
	{
		if (type == MUSIC)
		{
			Mix_PlayMusic(m_Musics[title], -1);
		}
		else if (type == CHUNK)
		{
			Mix_PlayChannel(-1, m_Chunks[title], 0);
		}
	}

	void AudioManager::pause(std::string title, SOUND_TYPE type)
	{
		if (type == MUSIC && Mix_PlayingMusic())
		{
			Mix_PauseMusic();
		}
		else if (type == CHUNK && Mix_Playing(-1))
		{
			Mix_Pause(-1);
		}
	}

	void AudioManager::resume(std::string title, SOUND_TYPE type)
	{
		if (type == MUSIC && Mix_PausedMusic())
		{
			Mix_ResumeMusic();
		}
		else if (type == CHUNK)
		{
			Mix_Resume(-1);
		}
	}

	void AudioManager::stop(std::string title, SOUND_TYPE type)
	{
		if (type == MUSIC)
		{
			Mix_HaltMusic();
		}
		else if (type == CHUNK)
		{
			Mix_HaltChannel(-1);
		}
	}

} }