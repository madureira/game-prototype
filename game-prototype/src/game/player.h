#pragma once

#include <string>
#include <vector>
#include <SDL2/SDL.h>
#include <glm/vec2.hpp>
#include "../core/entities/game_actor.h"
#include "../core/entities/animated_sprite.h"
#include "../core/inputs/input.h"
#include "../core/animations/animation.h"
#include "../core/events/event_manager.h"

namespace game {

	using namespace core;
	using namespace graphics;
	using namespace inputs;
	using namespace entities;
	using namespace animations;
	using namespace events;

	class Player : public GameActor, Observer {
	private:
		AnimatedSprite* m_AnimatedSprite;
		EventManager* m_EventManager;

		int m_Frames;
		bool m_IsBlocked;
		bool m_IsMovingUp;
		bool m_IsMovingDown;
		bool m_IsMovingLeft;
		bool m_IsMovingRight;
		int m_Speed;

	public:
		Player(SDL_Texture* playerTexture, glm::vec2 position, unsigned int speed, std::vector<Animation> animations, EventManager* eventManager);
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

		virtual void onNotify(const Entity& entity, Event event, void* pValue);

	private:
		bool isBlocked(std::string command);
		void moveUp();
		void moveDown();
		void moveLeft();
		void moveRight();
		void resetMovement();
		void notifyDisplacement(std::string direction);
	};
}