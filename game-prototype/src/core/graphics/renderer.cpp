#include "renderer.h"

namespace core { namespace graphics {

	Renderer::Renderer(SDL_Window* window)
	{
		m_Renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_TARGETTEXTURE);

		if (m_Renderer == NULL)
		{
			SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create renderer: %s", SDL_GetError());
		}

		int w, h;
		SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
		SDL_GetWindowSize(window, &w, &h);
		SDL_RenderSetLogicalSize(m_Renderer, w, h);

		// Background Black 
		SDL_SetRenderDrawColor(m_Renderer, 0, 0, 0, 255);
	}

	Renderer::~Renderer()
	{
		SDL_DestroyRenderer(m_Renderer);
	}

	void Renderer::clear()
	{
		SDL_RenderClear(m_Renderer);
	}

	void Renderer::draw(entities::Sprite* sprite)
	{
		SDL_RenderCopy(m_Renderer, sprite->getTexture(), &sprite->getSrcRect(), &sprite->getDestRect());
	}

	void Renderer::render()
	{
		SDL_RenderPresent(m_Renderer);
	}

	SDL_Texture* Renderer::createTexture(const std::string &filePath)
	{
		if (this->m_SpriteSheets.count(filePath) == 0) {
			SDL_Surface* temp = IMG_Load(filePath.c_str());
			if (temp == NULL)
			{
				printf("IMG_Load: %s\n", IMG_GetError());
				return NULL;
			}
			this->m_SpriteSheets[filePath] = SDL_CreateTextureFromSurface(m_Renderer, temp);
			SDL_FreeSurface(temp);
		}
		return this->m_SpriteSheets[filePath];
	}

	SDL_Texture* Renderer::createTextureLayer(const int width, const int height)
	{
		SDL_Texture* textureLayer = SDL_CreateTexture(m_Renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, width, height);
		SDL_SetTextureBlendMode(textureLayer, SDL_BLENDMODE_BLEND);
		return textureLayer;
	}

	void Renderer::setLayerTarget(SDL_Texture* textureLayer)
	{
		SDL_SetRenderTarget(m_Renderer, textureLayer);

		if (textureLayer == NULL)
		{
			SDL_SetRenderDrawBlendMode(m_Renderer, SDL_BLENDMODE_BLEND);
		}
		else {
			SDL_SetRenderDrawBlendMode(m_Renderer, SDL_BLENDMODE_NONE);
			SDL_SetRenderDrawColor(m_Renderer, 0, 0, 0, 0);
		}
	}

	FPS* Renderer::fpsCounter()
	{
		return new FPS(m_Renderer);
	}

	void Renderer::showCollisions(std::vector<SDL_Rect> collisions, SDL_Rect& viewport)
	{
		SDL_SetRenderDrawColor(m_Renderer, 68, 165, 26, 130); // green alpha
		for (std::vector<SDL_Rect>::iterator collision = collisions.begin(); collision != collisions.end(); ++collision) {
			SDL_Rect collisionRect = { collision->x + viewport.x, collision->y + viewport.y, collision->w, collision->h };
			SDL_RenderFillRect(m_Renderer, &collisionRect);
		}
	}

	void Renderer::setViewport(SDL_Rect* viewport)
	{
		SDL_RenderSetClipRect(m_Renderer, viewport);
	}

} }
