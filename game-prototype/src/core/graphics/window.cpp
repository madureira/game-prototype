#include "window.h"

namespace core { namespace graphics {

	Window::Window(const char* title, int width, int height, bool fullScreen, bool debugMode)
	{
		m_Title = title;
		m_Width = width;
		m_Height = height;
		m_FullScreen = fullScreen;
		m_DebugMode = debugMode;
		m_Closed = true;
		m_Resized = false;
		if (init())
		{
			m_Closed = false;
		}
		else {
			printf("Could not initalize SDL");
		}

	}

	Window::~Window()
	{
		
	}

	Renderer* Window::createRenderer() const
	{
		return new Renderer(m_Window, m_Width, m_Height, m_DebugMode);
	}

	bool Window::isClosed()
	{
		return m_Closed;
	}

	void Window::close()
	{
		m_Closed = true;
	}

	void Window::destroy()
	{
		SDL_DestroyWindow(this->m_Window);
		IMG_Quit();
		TTF_Quit();
		SDL_Quit();
	}

	bool Window::init()
	{
		if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		{
			SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to initialize SDL: %s", SDL_GetError());
			return false;
		}

		if (m_FullScreen) {
			m_Window = SDL_CreateWindow(m_Title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_Width, m_Height, SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_FULLSCREEN);
			SDL_ShowCursor(SDL_DISABLE);
		}
		else {
			m_Window = SDL_CreateWindow(m_Title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_Width, m_Height, SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
		}

		if (m_Window == NULL)
		{
			SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Could not create window: %s", SDL_GetError());
			return false;
		}

		if (!IMG_Init(IMG_INIT_PNG))
		{
			SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "IMG_INIT_PNG: %s", SDL_GetError());
			return false;
		}

		if (TTF_Init() == -1)
		{
			SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to initialize TTF %s", SDL_GetError());
			return false;
		}

		if (TTF_OpenFont("assets/fonts/Roboto-Regular.ttf", 90) == nullptr) {
			SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to load sketchy.ttf %s", SDL_GetError());
			return false;
		}

		return true;
	}

} }