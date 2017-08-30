#include "fps.h"

namespace core { namespace graphics {

	FPS::FPS(SDL_Renderer* renderer, SDL_Texture* targetTexture)
	{
		this->m_Renderer = renderer;
		this->m_TargetTexture = targetTexture;
		this->m_FPS = 0;

		memset(this->m_Frametimes, 0, sizeof(this->m_Frametimes));
		this->m_Framecount = 0;
		this->m_Frametimelast = SDL_GetTicks();
		this->m_Font = TTF_OpenFont("assets/fonts/Roboto-Regular.ttf", 26);
		this->m_TextColor = { 76, 153, 0, 0 };
		this->m_BackgroundColor = { 0, 0, 0 };
	}

	FPS::~FPS()
	{
		SDL_FreeSurface(this->m_TextSurface);
		SDL_DestroyTexture(this->m_TargetTexture);
		SDL_DestroyTexture(this->m_Text);
		TTF_CloseFont(this->m_Font);
	}

	void FPS::show()
	{
		Uint32 frametimesindex;
		Uint32 getticks;
		Uint32 count;
		Uint32 i;

		frametimesindex = this->m_Framecount % FRAME_VALUES;
		getticks = SDL_GetTicks();
		this->m_Frametimes[frametimesindex] = getticks - this->m_Frametimelast;
		this->m_Frametimelast = getticks;
		this->m_Framecount++;

		if (this->m_Framecount < FRAME_VALUES) {
			count = this->m_Framecount;
		}
		else {
			count = FRAME_VALUES;
		}

		this->m_FPS = 0;
		for (i = 0; i < count; i++)
		{
			this->m_FPS += this->m_Frametimes[i];
		}

		this->m_FPS /= count;
		this->m_FPS = 1000.f / this->m_FPS;

		std::string fpsText("FPS: ");
		fpsText.append(std::to_string((int)this->m_FPS));

		this->m_TextSurface = TTF_RenderText_Shaded(this->m_Font, fpsText.c_str(), this->m_TextColor, this->m_BackgroundColor);
		this->m_Text = SDL_CreateTextureFromSurface(this->m_Renderer, this->m_TextSurface);

		SDL_FreeSurface(this->m_TextSurface);
		m_RenderQuad = { 0, 0, this->m_TextSurface->w, this->m_TextSurface->h };

		SDL_SetRenderTarget(this->m_Renderer, this->m_TargetTexture);
		SDL_RenderCopy(this->m_Renderer, this->m_Text, &this->m_RenderQuad, &this->m_RenderQuad);
		SDL_DestroyTexture(this->m_Text);
	}

} }