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
		std::map<std::string, SDL_Texture*> m_SpriteSheets;

	public:
		Renderer(SDL_Window* SDLWindow);
		~Renderer();
		void clear();
		void draw(Sprite* sprite);
		void render();
		SDL_Texture* createTexture(const std::string &filePath);
		SDL_Texture* createTextureLayer(const int width, const int height);
		void setLayerTarget(SDL_Texture* textureLayer);
		FPS* fpsCounter();
		void setViewport(SDL_Rect* viewport);
		void showCollisions(std::vector<SDL_Rect> collisions, SDL_Rect& viewport);
	};

} }