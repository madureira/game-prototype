#pragma once

#include <string>
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
		AnimatedSprite* m_AnimatedSprite;
		std::vector<SDL_Rect>* m_Collisions;
		std::vector<glm::vec2>* m_Slopes;
		int m_Frames;
		bool m_IsBlocked;
		bool m_IsMovingUp;
		bool m_IsMovingDown;
		bool m_IsMovingLeft;
		bool m_IsMovingRight;
		int m_Speed;

	public:
		Player(SDL_Texture* playerTexture, glm::vec2 position, unsigned int speed, std::vector<Animation> animations, std::vector<SDL_Rect>* collisions, std::vector<glm::vec2>* slopes);
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
		glm::vec2 getDirection();
		inline AnimatedSprite* getSprite() { return m_AnimatedSprite; }
		inline bool isMovingUp() { return m_IsMovingUp; }
		inline bool isMovingDown() { return m_IsMovingDown; }
		inline bool isMovingLeft() { return m_IsMovingLeft; }
		inline bool isMovingRight() { return m_IsMovingRight; }
		inline int getSpeed() { return m_Speed; }

	private:
		bool isBlocked(std::string command);
		void moveUp();
		void moveDown();
		void moveLeft();
		void moveRight();
		void resetMovement();

	};
}