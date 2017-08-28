#pragma once

#include <map>
#include <vector>
#include <string>
#include <SDL2/SDL.h>
#include <SDL_image.h>
#include "../entities/sprite.h"
#include "fps.h"

namespace core { namespace graphics {

	using namespace entities;

	class Renderer {
	private:
		SDL_Renderer* m_Renderer;
		SDL_Texture* m_TargetTexture;
		SDL_Texture* m_FixedLayer;
		std::map<std::string, SDL_Texture*> m_SpriteSheets;
		int m_TargetPosX;
		int m_TargetPosY;
		unsigned int m_TargetWidth;
		unsigned int m_TargetHeight;
		unsigned int m_WindowWidth;
		unsigned int m_WindowHeight;

	public:
		Renderer(SDL_Window* SDLWindow, unsigned int winWidth, unsigned int winHeight);
		~Renderer();
		void clear();
		void draw(Sprite* sprite);
		void render();
		void setRendererPosition(int x, int y);
		void setRendererSize(unsigned int width, unsigned int height);
		SDL_Texture* createTexture(const std::string &filePath);
		void showCollisions(std::vector<SDL_Rect> collisions);
		FPS* fpsCounter();

	private:
		void createFixedLayer();
		void createRendererTarget();
		SDL_Texture* createTransparentTargetTexture(unsigned int width, unsigned int height);
	};

} }