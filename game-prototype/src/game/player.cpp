#include "player.h"

namespace game {

	Player::Player(SDL_Texture* playerTexture, int x, int y, std::vector<Animation> animations, std::vector<SDL_Rect>* collisions, std::vector<glm::vec2>* slopes, SDL_Rect* mapSize, SDL_Rect* viewport)
	{
		m_AnimatedSprite = new AnimatedSprite(playerTexture, x, y, animations);
		m_Collisions = collisions;
		m_Slopes = slopes;
		m_MapSize = mapSize;
		m_Viewport = viewport;
	}

	Player::~Player()
	{
		
	}

	void Player::idle()
	{
		m_AnimatedSprite->play("idle");
	}

	void Player::up()
	{
		m_AnimatedSprite->play("walk_up");
		moveUp();
	}

	void Player::down()
	{
		m_AnimatedSprite->play("walk_down");
		moveDown();
	}

	void Player::left()
	{
		m_AnimatedSprite->play("walk_left");
		moveLeft();
	}

	void Player::right()
	{
		m_AnimatedSprite->play("walk_right");
		moveRight();
	}

	void Player::upLeft()
	{
		m_AnimatedSprite->play("walk_up");
		moveUp();
		moveLeft();
	}

	void Player::upRight()
	{
		m_AnimatedSprite->play("walk_up");
		moveUp();
		moveRight();
	}

	void Player::downLeft()
	{
		m_AnimatedSprite->play("walk_down");
		moveDown();
		moveLeft();
	}

	void Player::downRight()
	{
		m_AnimatedSprite->play("walk_down");
		moveDown();
		moveRight();
	}

	bool Player::isBlocked(std::string command)
	{
		bool blocked = false;

		SDL_Rect player = m_AnimatedSprite->getDestRect();
		SDL_Rect playerBox = { player.x + 10, player.y + 30, player.w - 30, player.h - 40 };

		if (command == "up") {
			playerBox.y -= PLAYER_SPEED;
		}
		else if (command == "down") {
			playerBox.y += PLAYER_SPEED;
		}

		if (command == "right") {
			playerBox.x += PLAYER_SPEED;
		}
		else if (command == "left") {
			playerBox.x -= PLAYER_SPEED;
		}

		for (std::vector<SDL_Rect>::iterator collision = m_Collisions->begin(); collision != m_Collisions->end(); ++collision) {
			SDL_Rect collisionBox = { collision->x + PLAYER_SPEED, collision->y + PLAYER_SPEED, collision->w, collision->h };

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

	void Player::setViewport(const bool updateViewportX, const bool updateViewportY)
	{
		m_NeedUpdateViewportX = updateViewportX;
		m_NeedUpdateViewportY = updateViewportY;
	}

	void Player::moveUp()
	{
		if (!isBlocked("up"))
		{
			SDL_Rect player = m_AnimatedSprite->getDestRect();
			if (m_NeedUpdateViewportY) {
				if (m_Viewport->y <= 0 || (player.y + player.h / 2) >= m_Viewport->y + m_Viewport->h / 2)
				{
					player.y -= PLAYER_SPEED;
				}
				else {
					player.y -= PLAYER_SPEED;
					m_Viewport->y -= PLAYER_SPEED;
				}
			}
			else {
				player.y -= PLAYER_SPEED;
			}
			m_AnimatedSprite->setDestRect(player);
		}
	}

	void Player::moveDown()
	{
		if (!isBlocked("down"))
		{
			SDL_Rect player = m_AnimatedSprite->getDestRect();
			if (m_NeedUpdateViewportY)
			{
				if ((player.y + player.h / 2 <= m_Viewport->h / 2) || (m_Viewport->y + PLAYER_SPEED >= m_MapSize->h - m_Viewport->h))
				{
					player.y += PLAYER_SPEED;
				}
				else {
					player.y += PLAYER_SPEED;
					m_Viewport->y += PLAYER_SPEED;
				}
			}
			else {
				player.y += PLAYER_SPEED;
			}
			m_AnimatedSprite->setDestRect(player);
		}
	}

	void Player::moveLeft()
	{
		if (!isBlocked("left"))
		{
			SDL_Rect player = m_AnimatedSprite->getDestRect();
			if (m_NeedUpdateViewportX)
			{
				if (m_Viewport->x <= 0 || (player.x + player.w / 2) >= m_Viewport->x + m_Viewport->w / 2)
				{
					player.x -= PLAYER_SPEED;
				}
				else {
					player.x -= PLAYER_SPEED;
					m_Viewport->x -= PLAYER_SPEED;
				}
			}
			else
			{
				player.x -= PLAYER_SPEED;
			}
			m_AnimatedSprite->setDestRect(player);
		}
	}

	void Player::moveRight()
	{
		if (!isBlocked("right"))
		{
			SDL_Rect player = m_AnimatedSprite->getDestRect();
			if (m_NeedUpdateViewportX)
			{
				if ((player.x + player.w / 2 <= m_Viewport->x + m_Viewport->w / 2) || (m_Viewport->x >= m_MapSize->w - m_Viewport->w))
				{
					player.x += PLAYER_SPEED;
				}
				else {
					player.x += PLAYER_SPEED;
					m_Viewport->x += PLAYER_SPEED;
				}
			}
			else {
				player.x += PLAYER_SPEED;
			}
			m_AnimatedSprite->setDestRect(player);
		}
	}

}