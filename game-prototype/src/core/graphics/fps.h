#pragma once

#include <string>
#include <SDL2/SDL.h>
#include <SDL_ttf.h>

namespace core { namespace graphics {

	class FPS {
	private:
		static const int FRAME_VALUES = 10;
		float m_FPS;
		SDL_Renderer* m_Renderer;
		SDL_Surface* m_TextSurface;
		SDL_Texture* m_TargetTexture;
		SDL_Texture* m_Text;
		TTF_Font* m_Font;
		Uint32 m_Frametimes[FRAME_VALUES];
		Uint32 m_Frametimelast;
		Uint32 m_Framecount;
		SDL_Color m_TextColor;
		SDL_Color m_BackgroundColor;
		SDL_Rect m_RenderQuad;

	public:
		FPS(SDL_Renderer* renderer, SDL_Texture* targetTexture);
		~FPS();
		void show();
	};

} }