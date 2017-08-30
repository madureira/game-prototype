#include "static_sprite.h"

namespace core { namespace entities {

	StaticSprite::StaticSprite(SDL_Texture* texture, float destX, float destY, int width, int height)
	{
		this->m_Texture = texture;
		this->m_WindowRect.x = destX;
		this->m_WindowRect.y = destY;
		this->m_WindowRect.w = width;
		this->m_WindowRect.h = height;

		SDL_QueryTexture(texture, NULL, NULL, &this->m_TextureRect.w, &this->m_TextureRect.h);
	}

	StaticSprite::~StaticSprite()
	{

	}

} }