#pragma once

#include <string>
#include <vector>
#include <SDL2/SDL.h>

namespace core { namespace animations {

	struct Frame {
		SDL_Rect frame;
		int duration;
		bool rotated;

		Frame(SDL_Rect f, int d, bool r)
			: frame(f), duration(d), rotated(r) {}
	};

	class Animation
	{
	private:
		std::string m_Title;
		int m_SpriteWidth;
		int m_SpriteHeight;
		std::vector<Frame> m_Frames;

	public:
		Animation(std::string title, int spriteWidth, int spriteHeight, std::vector<Frame> frames);
		~Animation();

		std::string getTitle() const { return m_Title; }
		std::vector<Frame> getFrames() const { return m_Frames; }
		int getSpriteWidth() const { return m_SpriteWidth; }
		int getSpriteHeight() const { return m_SpriteHeight; }
	};

} }