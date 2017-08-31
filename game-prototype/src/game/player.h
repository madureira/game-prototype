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
		int m_Speed;
		bool m_IsBlocked;
		bool m_IsMovingUp;
		bool m_IsMovingDown;
		bool m_IsMovingLeft;
		bool m_IsMovingRight;

	public:
		Player(SDL_Texture* playerTexture, glm::vec2 position, unsigned int speed, std::vector<Animation> animations, EventManager* eventManager);
		~Player();

		glm::vec2 getDirection();
		inline AnimatedSprite* getSprite() { return m_AnimatedSprite; }

		virtual void idle() override;
		virtual void up() override;
		virtual void down() override;
		virtual void left() override;
		virtual void right() override;
		virtual void upLeft() override;
		virtual void upRight() override;
		virtual void downLeft() override;
		virtual void downRight() override;

		virtual void onNotify(Event event) override;
		virtual void onNotify(Event event, std::string data) override;
		virtual void onNotify(Event event, glm::vec4 data) override {};

	private:
		void moveUp();
		void moveDown();
		void moveLeft();
		void moveRight();
		void resetMovements();
		void notifyDisplacement(std::string direction);
		void playSoundEffect(std::string soundEffect);
	};
}