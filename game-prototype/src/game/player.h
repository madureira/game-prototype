#pragma once

#include <vector>
#include <SDL2/SDL.h>
#include <glm/vec2.hpp>
#include "../core/entities/game_actor.h"
#include "../core/entities/animated_sprite.h"
#include "../core/inputs/input.h"
#include "../core/animations/animation.h"

namespace game {

	using namespace core;
	using namespace graphics;
	using namespace inputs;
	using namespace entities;
	using namespace animations;

	class Player : public GameActor {
	private:
		static const int PLAYER_SPEED = 3;
		AnimatedSprite* m_AnimatedSprite;
		std::vector<SDL_Rect>* m_Collisions;
		std::vector<glm::vec2>* m_Slopes;
		int m_Speed;
		int m_Frames;
		SDL_Rect* m_Viewport;
		SDL_Rect* m_MapSize;
		bool m_IsBlocked;
		bool m_NeedUpdateViewportX;
		bool m_NeedUpdateViewportY;

	public:
		Player(SDL_Texture* playerTexture, int x, int y, std::vector<Animation> animations, std::vector<SDL_Rect>* collisions, std::vector<glm::vec2>* slopes, SDL_Rect* mapSize, SDL_Rect* viewport);
		~Player();
		void idle();
		void up();
		void down();
		void left();
		void right();
		void upLeft();
		void upRight();
		void downLeft();
		void downRight();
		bool isBlocked(std::string command);
		void setViewport(const bool updateViewportX, const bool updateViewportY);
		inline AnimatedSprite* getSprite() { return m_AnimatedSprite; }

	private:
		void moveUp();
		void moveDown();
		void moveLeft();
		void moveRight();

	};
}