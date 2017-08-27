#pragma once

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "renderer.h"

namespace core { namespace graphics {

	class Window {
	private:
		SDL_Window* m_Window;
		const char* m_Title;
		int m_Width;
		int m_Height;
		bool m_FullScreen;
		bool m_Closed;
		bool m_Resized;

	public:
		Window(const char* title, int width, int height, bool fullScreen);
		~Window();
		Renderer* createRenderer() const;
		bool isClosed();
		void close();
		void destroy();
		int getWidth() { return m_Width; }
		int getHeight() { return m_Height; }
		void setWidth(int width) { m_Width = width; }
		void setHeight(int height) { m_Height = height; }
		void setResizing(bool value) { m_Resized = value; }
		bool isResizing() { return m_Resized; }

	private:
		bool init();
	};

} }