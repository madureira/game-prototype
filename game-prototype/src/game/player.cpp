#include "player.h"

namespace game {

	Player::Player(SDL_Texture* playerTexture, glm::vec2 position, unsigned int speed, std::vector<Animation> animations, std::vector<SDL_Rect>* collisions, std::vector<glm::vec2>* slopes)
	{
		this->m_AnimatedSprite = new AnimatedSprite(playerTexture, position.x, position.y, animations);
		this->m_Collisions = collisions;
		this->m_Slopes = slopes;
		this->m_Speed = speed;
	}

	Player::~Player()
	{
		delete this->m_AnimatedSprite;
	}

	void Player::idle()
	{
		this->resetMovement();
		this->m_AnimatedSprite->play("idle");
	}

	void Player::up()
	{
		this->resetMovement();
		this->m_AnimatedSprite->play("walk_up");
		this->moveUp();
	}

	void Player::down()
	{
		this->resetMovement();
		this->m_AnimatedSprite->play("walk_down");
		this->moveDown();
	}

	void Player::left()
	{
		this->resetMovement();
		this->m_AnimatedSprite->play("walk_left");
		this->moveLeft();
	}

	void Player::right()
	{
		this->resetMovement();
		this->m_AnimatedSprite->play("walk_right");
		this->moveRight();
	}

	void Player::upLeft()
	{
		this->resetMovement();
		this->m_AnimatedSprite->play("walk_up");
		this->moveUp();
		this->moveLeft();
	}

	void Player::upRight()
	{
		this->resetMovement();
		this->m_AnimatedSprite->play("walk_up");
		this->moveUp();
		this->moveRight();
	}

	void Player::downLeft()
	{
		this->resetMovement();
		this->m_AnimatedSprite->play("walk_down");
		this->moveDown();
		this->moveLeft();
	}

	void Player::downRight()
	{
		this->resetMovement();
		this->m_AnimatedSprite->play("walk_down");
		this->moveDown();
		this->moveRight();
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

		SDL_Rect player = this->m_AnimatedSprite->getDestRect();
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

		for (std::vector<SDL_Rect>::iterator collision = this->m_Collisions->begin(); collision != this->m_Collisions->end(); ++collision) {
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
		if (!this->isBlocked("up"))
		{
			this->m_IsMovingUp = true;
			SDL_Rect player = this->m_AnimatedSprite->getDestRect();
			player.y -= this->getSpeed();
			this->m_AnimatedSprite->setDestRect(player);
		}
	}

	void Player::moveDown()
	{
		if (!this->isBlocked("down"))
		{
			this->m_IsMovingDown = true;
			SDL_Rect player = this->m_AnimatedSprite->getDestRect();
			player.y += this->getSpeed();
			this->m_AnimatedSprite->setDestRect(player);
		}
	}

	void Player::moveLeft()
	{
		if (!this->isBlocked("left"))
		{
			this->m_IsMovingLeft = true;
			SDL_Rect player = this->m_AnimatedSprite->getDestRect();
			player.x -= this->getSpeed();
			this->m_AnimatedSprite->setDestRect(player);
		}
	}

	void Player::moveRight()
	{
		if (!this->isBlocked("right"))
		{
			this->m_IsMovingRight = true;
			SDL_Rect player = this->m_AnimatedSprite->getDestRect();
			player.x += this->getSpeed();
			this->m_AnimatedSprite->setDestRect(player);
		}
	}

	void Player::resetMovement()
	{
		this->m_IsMovingUp = false;
		this->m_IsMovingDown = false;
		this->m_IsMovingRight = false;
		this->m_IsMovingLeft = false;
	}

}