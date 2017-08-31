#include "trigger.h"

namespace core { namespace entities {

	Trigger::Trigger(std::string name, int x, int y, unsigned width, unsigned height) :
		m_Name(name), m_X(x), m_Y(y), m_Width(width), m_Height(height)
	{
		this->m_IsActive = false;
	}

	Trigger::~Trigger()
	{
		
	}

	TriggerEvent Trigger::getEvent(int x, int y, int w, int h)
	{
		SDL_Rect target = { x, y, w, h };

		if (!this->isActive() && this->contains(target))
		{
			this->m_IsActive = true;
			return ON_ENTER;
		}
		else if (this->isActive() && !this->contains(target))
		{
			this->m_IsActive = false;
			return ON_LEAVE;
		}

		return INVACTIVE;
	}

	bool Trigger::contains(SDL_Rect other)
	{
		return (this->m_X <= other.x &&
				this->m_Y <= other.y &&
				this->m_X + this->m_Width >= other.x + other.w &&
				this->m_Y + this->m_Height >= other.y + other.h);
	}

} }