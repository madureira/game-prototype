#include "audio_manager.h"

namespace core { namespace audio {

	AudioManager::AudioManager(EventManager* eventManager)
	{
		this->m_EventManager = eventManager;

		int result = Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

		if (result < 0)
		{
			printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
		}

		result = Mix_AllocateChannels(ALLOCATED_CHANNELS);

		if (result < 0)
		{
			printf("Unable to allocate mixing channels: %s\n", Mix_GetError());
		}

		this->m_EventManager->addObserver(this);
	}

	AudioManager::~AudioManager()
	{
		for (auto& music : this->m_Musics)
		{
			Mix_FreeMusic(music.second);
		}

		for (auto& chunk : this->m_Effects)
		{
			Mix_FreeChunk(chunk.second);
		}

		m_Musics.clear();
		m_Effects.clear();
		Mix_Quit();
	}

	void AudioManager::onNotify(Event event, std::string sound, int volume, int loops)
	{
		if (event == AUDIO_PLAY_EFFECT)
		{
			this->play(sound, EFFECT, volume, loops);
		}
		else if (event == AUDIO_PLAY_MUSIC)
		{
			this->play(sound, MUSIC, volume, loops);
		}
	}

	void AudioManager::onNotify(Event event, std::string sound)
	{
		if (event == AUDIO_STOP_EFFECT)
		{
			this->stop(sound, EFFECT);
		}
		else if (event == AUDIO_STOP_MUSIC)
		{
			this->stop(sound, MUSIC);
		}
	}

	bool AudioManager::load(std::string sound, std::string audioFile, SOUND_TYPE type)
	{
		if (type == MUSIC)
		{
			this->m_Musics[sound] = Mix_LoadMUS(audioFile.c_str());
			if (this->m_Musics[sound] == NULL)
			{
				printf("Failed to load music! SDL_mixer Error: %s\n", Mix_GetError());
				return false;
			}
		}
		else if (type == EFFECT)
		{
			int usedChannels = this->m_Channels.size();
			int freeChannel = 0;

			if (usedChannels < ALLOCATED_CHANNELS)
			{
				freeChannel = usedChannels + 1;
				this->m_Channels[sound] = freeChannel;

				this->m_Effects[sound] = Mix_LoadWAV(audioFile.c_str());
				if (this->m_Effects[sound] == NULL)
				{
					printf("Failed to load sound effect! SDL_mixer Error: %s\n", Mix_GetError());
					return false;
				}
			}
			else
			{
				printf("SDL_mixer Error: There is no free channel to allocate!");
				return false;
			}
		}

		return true;
	}

	void AudioManager::play(std::string sound, SOUND_TYPE type, int volume, int loops)
	{
		if (volume >= 100)
		{
			volume = MIX_MAX_VOLUME;
		}
		else if (volume < 0)
		{
			volume = 0;
		}

		if (type == MUSIC)
		{
			Mix_PlayMusic(this->m_Musics[sound], loops);
			Mix_VolumeMusic(volume);
		}
		else if (type == EFFECT && !this->isPlayingEffect(sound))
		{	
			Mix_PlayChannel(this->m_Channels[sound], this->m_Effects[sound], loops);
			Mix_VolumeChunk(this->m_Effects[sound], volume);
		}
	}

	void AudioManager::pause(std::string sound, SOUND_TYPE type)
	{
		if (type == MUSIC && Mix_PlayingMusic())
		{
			Mix_PauseMusic();
		}
		else if (type == EFFECT && this->isPlayingEffect(sound))
		{
			Mix_Pause(this->m_Channels[sound]);
		}
	}

	void AudioManager::resume(std::string sound, SOUND_TYPE type)
	{
		if (type == MUSIC && Mix_PausedMusic())
		{
			Mix_ResumeMusic();
		}
		else if (type == EFFECT)
		{
			Mix_Resume(this->m_Channels[sound]);
		}
	}

	void AudioManager::stop(std::string sound, SOUND_TYPE type)
	{
		if (type == MUSIC)
		{
			Mix_HaltMusic();
		}
		else if (type == EFFECT && this->isPlayingEffect(sound))
		{
			Mix_HaltChannel(this->m_Channels[sound]);
		}
	}

	bool AudioManager::isPlayingEffect(std::string sound)
	{
		return Mix_Playing(this->m_Channels[sound]) != 0;
	}

} }