#include "window.h"

namespace core { namespace graphics {

	Window::Window(const char* title, int width, int height, bool fullScreen, bool debugMode)
	{
		this->m_Title = title;
		this->m_Width = width;
		this->m_Height = height;
		this->m_FullScreen = fullScreen;
		this->m_DebugMode = debugMode;
		this->m_Closed = true;
		this->m_Resized = false;

		if (this->init())
		{
			this->m_Closed = false;
		}
		else {
			printf("Could not initalize SDL");
		}
	}

	Window::~Window()
	{
		SDL_DestroyWindow(this->m_Window);
		IMG_Quit();
		TTF_Quit();
		SDL_Quit();
	}

	Renderer Window::createRenderer() const
	{
		return Renderer(this->m_Window, this->m_Width, this->m_Height, this->m_DebugMode);
	}

	bool Window::isClosed()
	{
		return this->m_Closed;
	}

	void Window::close()
	{
		this->m_Closed = true;
	}

	bool Window::init()
	{
		if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		{
			SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to initialize SDL: %s", SDL_GetError());
			return false;
		}

		Uint32 flags = SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI;

		if (this->m_FullScreen) {
			flags = SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_FULLSCREEN;
			SDL_ShowCursor(SDL_DISABLE);
		}

		this->m_Window = SDL_CreateWindow(this->m_Title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, this->m_Width, this->m_Height, flags);

		if (this->m_Window == NULL)
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

		if (TTF_OpenFont("assets/fonts/core/roboto-regular.ttf", 90) == nullptr) {
			SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to load sketchy.ttf %s", SDL_GetError());
			return false;
		}

		return true;
	}

} }