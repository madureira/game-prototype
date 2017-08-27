#include "fps.h"

namespace core { namespace graphics {

	FPS::FPS(SDL_Renderer* renderer)
	{
		m_Renderer = renderer;
		m_FPS = 0;

		memset(m_Frametimes, 0, sizeof(m_Frametimes));
		m_Framecount = 0;
		m_Frametimelast = SDL_GetTicks();
		m_Font = TTF_OpenFont("assets/fonts/Roboto-Regular.ttf", 26);
		m_TextColor = { 76, 153, 0, 0 };
		m_BackgroundColor = { 0, 0, 0 };


	}

	FPS::~FPS()
	{
		TTF_CloseFont(m_Font);
	}

	void FPS::show()
	{
		Uint32 frametimesindex;
		Uint32 getticks;
		Uint32 count;
		Uint32 i;

		frametimesindex = m_Framecount % FRAME_VALUES;
		getticks = SDL_GetTicks();
		m_Frametimes[frametimesindex] = getticks - m_Frametimelast;
		m_Frametimelast = getticks;
		m_Framecount++;

		if (m_Framecount < FRAME_VALUES) {
			count = m_Framecount;
		}
		else {
			count = FRAME_VALUES;
		}

		m_FPS = 0;
		for (i = 0; i < count; i++)
		{
			m_FPS += m_Frametimes[i];
		}

		m_FPS /= count;
		m_FPS = 1000.f / m_FPS;

		std::string fpsText("FPS: ");
		fpsText.append(std::to_string((int)m_FPS));

		m_TextSurface = TTF_RenderText_Shaded(m_Font, fpsText.c_str(), m_TextColor, m_BackgroundColor);
		m_Text = SDL_CreateTextureFromSurface(m_Renderer, m_TextSurface);
		
		int text_width = m_TextSurface->w;
		int text_height = m_TextSurface->h;
		SDL_FreeSurface(m_TextSurface);
		m_RenderQuad = { 0, 0, text_width, text_height };

		SDL_RenderCopy(m_Renderer, m_Text, &m_RenderQuad, &m_RenderQuad);
		SDL_DestroyTexture(m_Text);
	}

} }