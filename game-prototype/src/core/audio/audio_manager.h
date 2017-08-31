#pragma once

#include <map>
#include <string>
#include <SDL2/SDL.h>
#include <SDL_mixer.h>

#include "../events/observer.h"
#include "../events/event_manager.h"

namespace core { namespace audio {

	using namespace events;

	enum SOUND_TYPE {
		MUSIC,
		EFFECT
	};

	class AudioManager : public Observer
	{
	private:
		static const int ALLOCATED_CHANNELS = 16;

		std::map<std::string, Mix_Music*> m_Musics;
		std::map<std::string, Mix_Chunk*> m_Effects;
		std::map<std::string, int> m_Channels;
		EventManager* m_EventManager;

	public:
		AudioManager(EventManager* eventManager);
		~AudioManager();

		bool load(std::string sound, std::string audioFile, SOUND_TYPE type);
		void play(std::string sound, SOUND_TYPE type, int volume, int loops);
		void pause(std::string sound, SOUND_TYPE type);
		void resume(std::string sound, SOUND_TYPE type);
		void stop(std::string sound, SOUND_TYPE type);

		virtual void onNotify(Event event, std::string sound, int volume, int loops) override;
		virtual void onNotify(Event event, std::string sound) override;

	private:
		bool isPlayingEffect(std::string sound);
	};

} }