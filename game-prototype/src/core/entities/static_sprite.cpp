#include "static_sprite.h"

namespace core { namespace entities {

	StaticSprite::StaticSprite(SDL_Texture* texture, float destX, float destY, int width, int height)
	{
		m_Texture = texture;
		m_WindowRect.x = destX;
		m_WindowRect.y = destY;
		m_WindowRect.w = width;
		m_WindowRect.h = height;

		SDL_QueryTexture(texture, NULL, NULL, &m_TextureRect.w, &m_TextureRect.h);
	}

	StaticSprite::~StaticSprite()
	{

	}

} }