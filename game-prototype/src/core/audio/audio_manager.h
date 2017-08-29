#pragma once

#include <map>
#include <string>
#include <SDL2/SDL.h>
#include <SDL_mixer.h>

namespace core { namespace audio {

	enum SOUND_TYPE {
		MUSIC,
		EFFECT
	};

	class AudioManager {
	private:
		std::map<std::string, Mix_Music*> m_Musics;
		std::map<std::string, Mix_Chunk*> m_Effects;

	public:
		AudioManager();
		~AudioManager();

		bool load(std::string title, std::string audioFile, SOUND_TYPE type);
		void play(std::string title, SOUND_TYPE type, int volume, int loops);
		void pause(std::string title, SOUND_TYPE type);
		void resume(std::string title, SOUND_TYPE type);
		void stop(std::string title, SOUND_TYPE type);
	};

} }