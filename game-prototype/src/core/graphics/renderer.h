#pragma once

#include <map>
#include <vector>
#include <string>
#include <glm/vec2.hpp>
#include <SDL2/SDL.h>
#include <SDL_image.h>
#include "../entities/sprite.h"
#include "../entities/trigger.h"
#include "../entities/camera.h"
#include "fps.h"

namespace core { namespace graphics {

	using namespace entities;

	class Renderer {
	private:
		SDL_Renderer* m_Renderer;
		SDL_Texture* m_TargetTexture;
		SDL_Texture* m_FixedLayer;
		Camera* m_Camera;
		FPS* m_FPS;
		std::map<std::string, SDL_Texture*> m_SpriteSheets;
		std::vector<SDL_Rect> m_Collisions;
		std::vector<Trigger> m_Triggers;
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
		void setRendererSize(unsigned int width, unsigned int height);
		SDL_Texture* createTexture(const std::string &filePath);
		inline void setCamera(Camera* camera) { m_Camera = camera; }
		inline void setCollisions(std::vector<SDL_Rect> collisions) { m_Collisions = collisions; }
		inline void setTriggers(std::vector<Trigger> triggers) { m_Triggers = triggers; }

	private:
		void initFPSCounter();
		void createFixedLayer();
		void createRendererTarget();
		SDL_Texture* createTransparentTargetTexture(unsigned int width, unsigned int height);
		void showCollisions();
		void showTriggers();
		void updateRendererPosition();
		void showFps();
	};

} }