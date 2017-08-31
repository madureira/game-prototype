#pragma once

#include <vector>
#include <SDL2/SDL.h>
#include "../events/observer.h"
#include "../events/event_manager.h"

namespace core { namespace collisions {

	using namespace events;

	class CollisionsManager : public Observer
	{
	private:
		std::vector<SDL_Rect> m_Collisions;
		EventManager* m_EventManager;

	public:
		CollisionsManager(std::vector<SDL_Rect> collisions, EventManager* eventManager);
		~CollisionsManager();

		virtual void onNotify(const Entity& entity, Event event, void* pValue);

	private:
		bool isColliding(SDL_Rect target);
	};

} }