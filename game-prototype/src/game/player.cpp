#include "player.h"

namespace game {

	Player::Player(SDL_Texture* playerTexture, glm::vec2 position, unsigned int speed, std::vector<Animation> animations, std::vector<SDL_Rect>* collisions, std::vector<glm::vec2>* slopes)
	{
		m_AnimatedSprite = new AnimatedSprite(playerTexture, position.x, position.y, animations);
		m_Collisions = collisions;
		m_Slopes = slopes;
		m_Speed = speed;
	}

	Player::~Player()
	{
		
	}

	void Player::idle()
	{
		resetMovement();
		m_AnimatedSprite->play("idle");
	}

	void Player::up()
	{
		resetMovement();
		m_AnimatedSprite->play("walk_up");
		moveUp();
	}

	void Player::down()
	{
		resetMovement();
		m_AnimatedSprite->play("walk_down");
		moveDown();
	}

	void Player::left()
	{
		resetMovement();
		m_AnimatedSprite->play("walk_left");
		moveLeft();
	}

	void Player::right()
	{
		resetMovement();
		m_AnimatedSprite->play("walk_right");
		moveRight();
	}

	void Player::upLeft()
	{
		resetMovement();
		m_AnimatedSprite->play("walk_up");
		moveUp();
		moveLeft();
	}

	void Player::upRight()
	{
		resetMovement();
		m_AnimatedSprite->play("walk_up");
		moveUp();
		moveRight();
	}

	void Player::downLeft()
	{
		resetMovement();
		m_AnimatedSprite->play("walk_down");
		moveDown();
		moveLeft();
	}

	void Player::downRight()
	{
		resetMovement();
		m_AnimatedSprite->play("walk_down");
		moveDown();
		moveRight();
	}

	glm::vec2 Player::getDirection()
	{
		int vertical = 0;
		int horizontal = 0;

		if (this->isMovingUp())
		{
			vertical = -1;
		}
		else if (this->isMovingDown())
		{
			vertical = 1;
		}

		if (this->isMovingLeft())
		{
			horizontal = -1;
		}
		else if (this->isMovingRight())
		{
			horizontal = 1;
		}

		return glm::vec2(horizontal, vertical);
	}

	bool Player::isBlocked(std::string command)
	{
		bool blocked = false;

		SDL_Rect player = m_AnimatedSprite->getDestRect();
		SDL_Rect playerBox = { player.x + 10, player.y + 30, player.w - 30, player.h - 40 };

		if (command == "up") {
			playerBox.y -= this->getSpeed();
		}
		else if (command == "down") {
			playerBox.y += this->getSpeed();
		}

		if (command == "right") {
			playerBox.x += this->getSpeed();
		}
		else if (command == "left") {
			playerBox.x -= this->getSpeed();
		}

		for (std::vector<SDL_Rect>::iterator collision = m_Collisions->begin(); collision != m_Collisions->end(); ++collision) {
			SDL_Rect collisionBox = { collision->x + this->getSpeed(), collision->y + this->getSpeed(), collision->w, collision->h };

			if (playerBox.x <= collisionBox.x + collisionBox.w &&
				playerBox.x + playerBox.w >= collisionBox.x &&
				playerBox.y < collisionBox.y + collisionBox.h &&
				playerBox.h + playerBox.y >= collisionBox.y) {
				blocked = true;
				break;
			}
		}

		return blocked;
	}

	void Player::moveUp()
	{
		if (!isBlocked("up"))
		{
			m_IsMovingUp = true;
			SDL_Rect player = m_AnimatedSprite->getDestRect();
			player.y -= this->getSpeed();
			m_AnimatedSprite->setDestRect(player);
		}
	}

	void Player::moveDown()
	{
		if (!isBlocked("down"))
		{
			m_IsMovingDown = true;
			SDL_Rect player = m_AnimatedSprite->getDestRect();
			player.y += this->getSpeed();
			m_AnimatedSprite->setDestRect(player);
		}
	}

	void Player::moveLeft()
	{
		if (!isBlocked("left"))
		{
			m_IsMovingLeft = true;
			SDL_Rect player = m_AnimatedSprite->getDestRect();
			player.x -= this->getSpeed();
			m_AnimatedSprite->setDestRect(player);
		}
	}

	void Player::moveRight()
	{
		if (!isBlocked("right"))
		{
			m_IsMovingRight = true;
			SDL_Rect player = m_AnimatedSprite->getDestRect();
			player.x += this->getSpeed();
			m_AnimatedSprite->setDestRect(player);
		}
	}

	void Player::resetMovement()
	{
		m_IsMovingUp = false;
		m_IsMovingDown = false;
		m_IsMovingRight = false;
		m_IsMovingLeft = false;
	}

}