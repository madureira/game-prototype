#pragma once

#include <string>
#include <SDL2/SDL.h>
#include <glm/vec2.hpp>

namespace core { namespace entities {

	class Camera
	{
	private:
		int m_X;
		int m_Y;
		unsigned int m_Width;
		unsigned int m_Height;
		unsigned int m_Speed;
		int m_LevelWidth;
		int m_LevelHeight;
		bool m_UpdateX;
		bool m_UpdateY;

	public:
		Camera(SDL_Rect viewport, unsigned int speed, unsigned int levelWidth, unsigned int levelHeight);
		~Camera();

		bool isVisible(SDL_Rect object);
		glm::vec2 getPosition(SDL_Rect target, glm::vec2 direction);
	};

} }