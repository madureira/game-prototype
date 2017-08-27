#pragma once

#include <SDL2/SDL.h>
#include "../libs/json.hpp"

namespace core { namespace ase { 

	using json = nlohmann::json;

	class AseFrames
	{
	private:
		SDL_Rect m_Frame;
		bool m_Rotated;
		int m_Duration;

	public:
		AseFrames(json &frame);
		~AseFrames();

		SDL_Rect getFrame() const { return m_Frame; }
		bool isRotated() const { return m_Rotated; }
		int getDuration() const { return m_Duration; }
	};

} }