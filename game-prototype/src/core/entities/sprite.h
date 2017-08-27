#pragma once

#include <SDL2/SDL.h>
#include <SDL_image.h>

namespace core { namespace entities {

	class Sprite {
	protected:
		SDL_Texture* m_Texture;
		SDL_Rect m_TextureRect;
		SDL_Rect m_WindowRect;

	public:
		inline SDL_Texture* getTexture() { return m_Texture; }
		inline SDL_Rect getSrcRect() { return m_TextureRect; }
		inline SDL_Rect getDestRect() { return m_WindowRect; }
		inline void setSrcRect(SDL_Rect srcRect) { m_TextureRect = srcRect; }
		inline void setDestRect(SDL_Rect destRect) { m_WindowRect = destRect; }
	};

} }