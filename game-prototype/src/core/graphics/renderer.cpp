#include "renderer.h"

namespace core { namespace graphics {

	Renderer::Renderer(SDL_Window* window, unsigned int winWidth, unsigned int winHeight, bool debugMode)
	{
		this->m_DebugMode = debugMode;
		Uint32 flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE | SDL_RENDERER_PRESENTVSYNC;

		this->m_Renderer = SDL_CreateRenderer(window, -1, flags);

		if (this->m_Renderer == NULL)
		{
			SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create renderer: %s", SDL_GetError());
		}

		this->m_WindowWidth = winWidth;
		this->m_WindowHeight = winHeight;
		this->m_TargetWidth = winWidth;
		this->m_TargetHeight = winHeight;

		SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");
		SDL_RenderSetLogicalSize(this->m_Renderer, this->m_TargetWidth, this->m_TargetHeight);

		// Background Black 
		SDL_SetRenderDrawColor(this->m_Renderer, 0, 0, 0, 255);
		
		this->createRendererTarget();
		this->createFixedLayer();
		this->initFPSCounter();
	}

	Renderer::~Renderer()
	{
		SDL_DestroyTexture(this->m_TargetTexture);
		SDL_DestroyTexture(this->m_FixedLayer);
		SDL_DestroyRenderer(this->m_Renderer);
	}

	void Renderer::clear()
	{
		SDL_SetRenderTarget(this->m_Renderer, NULL);
		SDL_RenderClear(this->m_Renderer);

		SDL_SetRenderTarget(this->m_Renderer, this->m_TargetTexture);
		SDL_RenderClear(this->m_Renderer);

		if (this->m_DebugMode)
		{
			this->m_FPS->show();
		}
	}

	void Renderer::draw(entities::Sprite* sprite)
	{
		SDL_SetRenderTarget(this->m_Renderer, this->m_TargetTexture);
		SDL_RenderCopy(this->m_Renderer, sprite->getTexture(), &sprite->getSrcRect(), &sprite->getDestRect());
	}

	void Renderer::render()
	{
		SDL_Rect source = { this->m_TargetPosX, this->m_TargetPosY, this->m_WindowWidth, this->m_WindowHeight };
		SDL_Rect winRect = { 0, 0, this->m_WindowWidth, this->m_WindowHeight };

		if (source.x > 0)
		{
			source.x -= 1;
		}

		if (source.y > 0)
		{
			source.y -= 1;
		}

		SDL_SetRenderTarget(this->m_Renderer, NULL);
		SDL_RenderCopy(this->m_Renderer, this->m_TargetTexture, &source, &winRect);
		SDL_RenderCopy(this->m_Renderer, this->m_FixedLayer, &winRect, &winRect);
		SDL_RenderPresent(this->m_Renderer);
	}

	void Renderer::setRendererPosition(glm::vec2 position)
	{
		this->m_TargetPosX = position.x;
		this->m_TargetPosY = position.y;
	}

	void Renderer::setRendererSize(unsigned int width, unsigned int height)
	{
		this->m_TargetWidth = width;
		this->m_TargetHeight = height;
		this->createRendererTarget();
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
			this->m_SpriteSheets[filePath] = SDL_CreateTextureFromSurface(this->m_Renderer, temp);
			SDL_FreeSurface(temp);
		}
		return this->m_SpriteSheets[filePath];
	}

	void Renderer::showCollisions(std::vector<SDL_Rect> collisions)
	{
		if (this->m_DebugMode)
		{
			SDL_SetRenderTarget(this->m_Renderer, this->m_TargetTexture);
			SDL_SetRenderDrawBlendMode(m_Renderer, SDL_BLENDMODE_BLEND);
			SDL_SetRenderDrawColor(this->m_Renderer, 68, 165, 26, 130); // green alpha
			for (std::vector<SDL_Rect>::iterator collision = collisions.begin(); collision != collisions.end(); ++collision) {
				SDL_Rect collisionRect = { collision->x, collision->y, collision->w, collision->h };
				SDL_RenderFillRect(this->m_Renderer, &collisionRect);
			}
			SDL_SetRenderDrawColor(this->m_Renderer, 0, 0, 0, 255); // set black again
		}
	}

	void Renderer::initFPSCounter()
	{
		this->m_FPS = new FPS(this->m_Renderer, this->m_FixedLayer);
	}

	void Renderer::createFixedLayer()
	{
		this->m_FixedLayer = this->createTransparentTargetTexture(this->m_WindowWidth, this->m_WindowHeight);
	}

	void Renderer::createRendererTarget()
	{
		this->m_TargetTexture = this->createTransparentTargetTexture(this->m_TargetWidth, this->m_TargetHeight);
	}

	SDL_Texture* Renderer::createTransparentTargetTexture(unsigned int width, unsigned int height)
	{
		SDL_Texture* tex = SDL_CreateTexture(this->m_Renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, width, height);
		SDL_SetTextureBlendMode(tex, SDL_BLENDMODE_BLEND);
		return tex;
	}

} }
