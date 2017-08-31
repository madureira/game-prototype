#pragma once

#include <string>
#include <SDL2/SDL.h>

namespace core { namespace entities {

	enum TRIGGER_EVENTS
	{
		ON_ENTER,
		ON_LEAVE,
		INVACTIVE
	};

	class Trigger
	{
	private:
		std::string m_Name;
		int m_X;
		int m_Y;
		unsigned int m_Width;
		unsigned int m_Height;
		bool m_IsActive;

	public:
		Trigger(std::string name, int x, int y, unsigned width, unsigned height);
		~Trigger();

		TRIGGER_EVENTS getEvent(int x, int y, int w, int h);

		inline std::string getName() const { return m_Name; }
		inline int getX() const { return m_X; }
		inline int getY() const { return m_Y; }
		inline int getWidth() const { return m_Width; }
		inline int getHeight() const { return m_Height; }
		inline bool isActive() const { return m_IsActive; }

	private:
		bool contains(SDL_Rect other);
	};

} }