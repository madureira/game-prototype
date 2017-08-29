#include "camera.h"

namespace core { namespace entities {

	Camera::Camera(SDL_Rect viewport, unsigned int speed, unsigned int levelWidth, unsigned int levelHeight)
	{
		this->m_X = viewport.x;
		this->m_Y = viewport.y;
		this->m_Width = viewport.w;
		this->m_Height = viewport.h;
		this->m_Speed = speed;
		this->m_LevelWidth = levelWidth;
		this->m_LevelHeight = levelHeight;

		bool updateViewportX = false;
		bool updateViewportY = false;

		if (this->m_LevelWidth > this->m_Width)
		{
			m_UpdateX = true;
		}

		if (this->m_LevelHeight > this->m_Height)
		{
			m_UpdateY = true;
		}
	}

	Camera::~Camera()
	{

	}

	bool Camera::isVisible(SDL_Rect object)
	{
		return (object.x + object.w * 2 >= this->getX() + object.w &&
				object.y + object.h * 2 >= this->getY() + object.h &&
				object.x <= this->getX() + this->getWidth() &&
				object.y <= this->getY() + this->getHeight());
	}

	glm::vec2 Camera::getPosition(SDL_Rect target, glm::vec2 direction)
	{
		if (this->m_UpdateY) {
			// Moving UP
			if (direction.y == -1 && this->m_Y > 0 && (this->m_Y + this->m_Height / 2) >= (target.y + target.h / 2))
			{
				this->m_Y -= this->m_Speed;
			}

			// Moving DOWN
			if (direction.y == 1 && (target.y + target.h / 2 >= this->m_Height / 2) && (this->m_Y < this->m_LevelHeight - this->m_Height))
			{
				this->m_Y += this->m_Speed;
			}
		}

		if (this->m_UpdateX) {
			// Moving LEFT
			if (direction.x == -1 && this->m_X > 0 && (this->m_X + this->m_Width / 2) >= (target.x + target.w / 2))
			{
				this->m_X -= this->m_Speed;
			}

			// Moving RIGHT
			if (direction.x == 1 && (target.x + target.w / 2 >= this->m_Width / 2) && (this->m_X < this->m_LevelWidth - this->m_Width))
			{
				this->m_X += this->m_Speed;
			}
		}

		return glm::vec2(this->m_X, this->m_Y);
	}

} }