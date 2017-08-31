#pragma once

#include <map>
#include <vector>
#include <string>
#include <glm/vec2.hpp>
#include <SDL2/SDL.h>
#include <SDL_image.h>
#include "../entities/sprite.h"
#include "../entities/trigger.h"
#include "fps.h"

namespace core { namespace graphics {

	using namespace entities;

	class Renderer {
	private:
		SDL_Renderer* m_Renderer;
		SDL_Texture* m_TargetTexture;
		SDL_Texture* m_FixedLayer;
		FPS* m_FPS;
		std::map<std::string, SDL_Texture*> m_SpriteSheets;
		bool m_DebugMode;
		int m_TargetPosX;
		int m_TargetPosY;
		unsigned int m_TargetWidth;
		unsigned int m_TargetHeight;
		unsigned int m_WindowWidth;
		unsigned int m_WindowHeight;

	public:
		Renderer(SDL_Window* SDLWindow, unsigned int winWidth, unsigned int winHeight, bool debugMode);
		~Renderer();
		void clear();
		void draw(Sprite* sprite);
		void render();
		void setRendererPosition(glm::vec2 position);
		void setRendererSize(unsigned int width, unsigned int height);
		SDL_Texture* createTexture(const std::string &filePath);
		void showCollisions(std::vector<SDL_Rect> collisions);
		void showTriggers(std::vector<Trigger*> triggers);

	private:
		void initFPSCounter();
		void createFixedLayer();
		void createRendererTarget();
		SDL_Texture* createTransparentTargetTexture(unsigned int width, unsigned int height);
	};

} }