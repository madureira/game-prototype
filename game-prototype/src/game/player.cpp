#include "player.h"

namespace game {

	Player::Player(SDL_Texture* playerTexture, glm::vec2 position, unsigned int speed, std::vector<Animation> animations, EventManager* eventManager)
	{
		this->m_AnimatedSprite = new AnimatedSprite(playerTexture, position.x, position.y, animations);
		this->m_Speed = speed;
		this->m_EventManager = eventManager;
		this->m_EventManager->addObserver(this);
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

	void Player::onNotify(Event event, void* pValue)
	{
		if (event == PLAYER_BLOCKED)
		{
			this->m_IsBlocked = true;
		}
		else if (event == PLAYER_NOT_BLOCKED)
		{
			this->m_IsBlocked = false;
		}
		else if (event == PLAYER_TRIGGER_ON)
		{
			this->playSoundEffect("enter_door");
		}
	}

	bool Player::isBlocked()
	{
		return this->m_IsBlocked;
	}

	void Player::moveUp()
	{
		this->notifyDisplacement("up");
		if (!this->isBlocked())
		{
			this->m_IsMovingUp = true;
			SDL_Rect player = this->m_AnimatedSprite->getDestRect();
			player.y -= this->getSpeed();
			this->m_AnimatedSprite->setDestRect(player);
		}
	}

	void Player::moveDown()
	{
		this->notifyDisplacement("down");
		if (!this->isBlocked())
		{
			this->m_IsMovingDown = true;
			SDL_Rect player = this->m_AnimatedSprite->getDestRect();
			player.y += this->getSpeed();
			this->m_AnimatedSprite->setDestRect(player);
		}
	}

	void Player::moveLeft()
	{
		this->notifyDisplacement("left");
		if (!this->isBlocked())
		{
			this->m_IsMovingLeft = true;
			SDL_Rect player = this->m_AnimatedSprite->getDestRect();
			player.x -= this->getSpeed();
			this->m_AnimatedSprite->setDestRect(player);
		}
	}

	void Player::moveRight()
	{
		this->notifyDisplacement("right");
		if (!this->isBlocked())
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

	void Player::notifyDisplacement(std::string direction)
	{
		SDL_Rect player = this->m_AnimatedSprite->getDestRect();
		SDL_Rect playerBox = { player.x + 10, player.y + 25, player.w - 20, player.h - 25 };

		if (direction == "up") {
			playerBox.y -= this->getSpeed();
		}
		else if (direction == "down") {
			playerBox.y += this->getSpeed();
		}
		else if (direction == "right") {
			playerBox.x += this->getSpeed();
		}
		else if (direction == "left") {
			playerBox.x -= this->getSpeed();
		}

		this->m_EventManager->notify(PLAYER_WALK, &playerBox);
		this->playSoundEffect("steps");
	}

	void Player::playSoundEffect(std::string soundEffect)
	{
		this->m_EventManager->notify(AUDIO_PLAY_EFFECT, &soundEffect);
	}

}