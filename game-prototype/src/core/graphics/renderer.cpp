#include "renderer.h"

namespace core { namespace graphics {

	Renderer::Renderer(SDL_Window* window, unsigned int winWidth, unsigned int winHeight, bool debugMode)
	{
		this->m_DebugMode = debugMode;

		Uint32 flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE | SDL_RENDERER_PRESENTVSYNC;

		this->m_Renderer = SDL_CreateRenderer(window, -1, flags);

		if (this->m_Renderer == NULL)
			SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create renderer: %s", SDL_GetError());

		this->m_WindowWidth = winWidth;
		this->m_WindowHeight = winHeight;
		this->m_MainLayerWidth = winWidth;
		this->m_MainLayerHeight = winHeight;

		SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");
		SDL_RenderSetLogicalSize(this->m_Renderer, this->m_MainLayerWidth, this->m_MainLayerHeight);

		// Background Black
		SDL_SetRenderDrawColor(this->m_Renderer, 0, 0, 0, 255);

		this->createMainLayer();
		this->createFixedLayer();
		this->initFPSCounter();
	}

	Renderer::~Renderer()
	{
		for (std::map<std::string, SDL_Texture*>::iterator itr = this->m_SpriteSheets.begin(); itr != this->m_SpriteSheets.end(); itr++)
		{
			SDL_DestroyTexture(itr->second);
		}
		this->m_SpriteSheets.clear();
		this->m_Collisions.clear();
		this->m_Triggers.clear();

		delete this->m_FPS;
		SDL_DestroyTexture(this->m_MainLayer);
		SDL_DestroyTexture(this->m_FixedLayer);
		SDL_DestroyRenderer(this->m_Renderer);
	}

	void Renderer::clear()
	{
		SDL_SetRenderTarget(this->m_Renderer, NULL);
		SDL_RenderClear(this->m_Renderer);

		SDL_SetRenderTarget(this->m_Renderer, this->m_MainLayer);
		SDL_RenderClear(this->m_Renderer);
	}

	void Renderer::draw(entities::Sprite* sprite)
	{
		if (this->m_Camera == NULL) throw std::runtime_error("Error: Camera not found! Renderer need a Camera to draw visible sprites");

		if (this->m_Camera->isVisible(sprite->getDestRect())) // draws only visible sprites
		{
			SDL_SetRenderTarget(this->m_Renderer, this->m_MainLayer);
			SDL_Rect src = sprite->getSrcRect();
			SDL_Rect dest = sprite->getDestRect();
			SDL_RenderCopy(this->m_Renderer, sprite->getTexture(), &src, &dest);
		}
	}

	void Renderer::render()
	{
		this->updateRendererPosition();
		this->showFps();
		this->showCollisions();
		this->showTriggers();

		SDL_Rect source = { this->m_TargetPosX, this->m_TargetPosY, this->m_WindowWidth, this->m_WindowHeight };
		SDL_Rect winRect = { 0, 0, this->m_WindowWidth, this->m_WindowHeight };

		SDL_SetRenderTarget(this->m_Renderer, NULL);
		SDL_RenderCopy(this->m_Renderer, this->m_MainLayer, &source, &winRect);
		SDL_RenderCopy(this->m_Renderer, this->m_FixedLayer, &winRect, &winRect);
		SDL_RenderPresent(this->m_Renderer);
	}

	SDL_Texture* Renderer::createTexture(const std::string &filePath)
	{
		if (this->m_SpriteSheets.count(filePath) == 0)
		{
			SDL_Surface* temp = IMG_Load(filePath.c_str());
			if (temp == NULL)
			{
				printf("IMG_Load: %s\n", IMG_GetError());
				return NULL;
			}
			this->m_SpriteSheets[filePath] = SDL_CreateTextureFromSurface(this->m_Renderer, temp);
			SDL_FreeSurface(temp);
		}
		return this->m_SpriteSheets[filePath];
	}

	void Renderer::setSize(unsigned int width, unsigned int height)
	{
		this->m_MainLayerWidth = width;
		this->m_MainLayerHeight = height;
		this->createMainLayer();
	}

	void Renderer::showCollisions()
	{
		if (this->m_DebugMode && !this->m_Collisions.empty())
		{
			SDL_SetRenderTarget(this->m_Renderer, this->m_MainLayer);
			SDL_SetRenderDrawBlendMode(m_Renderer, SDL_BLENDMODE_BLEND);
			SDL_SetRenderDrawColor(this->m_Renderer, 68, 165, 26, 130); // green alpha
			for (auto& collision : this->m_Collisions)
			{
				SDL_Rect collisionRect = { collision.x, collision.y, collision.w, collision.h };
				SDL_RenderFillRect(this->m_Renderer, &collisionRect);
			}
			SDL_SetRenderDrawColor(this->m_Renderer, 0, 0, 0, 255); // set black again
		}
	}

	void Renderer::showTriggers()
	{
		if (this->m_DebugMode && !this->m_Triggers.empty())
		{
			SDL_SetRenderTarget(this->m_Renderer, this->m_MainLayer);
			SDL_SetRenderDrawBlendMode(m_Renderer, SDL_BLENDMODE_BLEND);
			SDL_SetRenderDrawColor(this->m_Renderer, 255, 0, 0, 130); // green alpha
			for (auto& trigger : this->m_Triggers)
			{
				SDL_Rect triggerRect = { trigger.getX(), trigger.getY(), trigger.getWidth(), trigger.getHeight() };
				SDL_RenderFillRect(this->m_Renderer, &triggerRect);
			}
			SDL_SetRenderDrawColor(this->m_Renderer, 0, 0, 0, 255); // set black again
		}
	}

	void Renderer::updateRendererPosition()
	{
		this->m_TargetPosX = this->m_Camera->getX();
		this->m_TargetPosY = this->m_Camera->getY();
	}

	void Renderer::initFPSCounter()
	{
		this->m_FPS = new FPS(this->m_Renderer, this->m_FixedLayer);
	}

	void Renderer::createFixedLayer()
	{
		this->m_FixedLayer = this->createTransparentTargetTexture(this->m_WindowWidth, this->m_WindowHeight);
	}

	void Renderer::createMainLayer()
	{
		this->m_MainLayer = this->createTransparentTargetTexture(this->m_MainLayerWidth, this->m_MainLayerHeight);
	}

	SDL_Texture* Renderer::createTransparentTargetTexture(unsigned int width, unsigned int height)
	{
		SDL_Texture* tex = SDL_CreateTexture(this->m_Renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, width, height);
		SDL_SetTextureBlendMode(tex, SDL_BLENDMODE_BLEND);
		return tex;
	}

	void Renderer::showFps()
	{
		if (this->m_DebugMode)
			this->m_FPS->show();
	}

} }
