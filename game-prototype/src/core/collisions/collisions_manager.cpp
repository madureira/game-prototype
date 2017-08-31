#include "collisions_manager.h"

namespace core { namespace collisions {

	CollisionsManager::CollisionsManager(std::vector<SDL_Rect> collisions, EventManager* eventManager)
		: m_Collisions(collisions), m_EventManager(eventManager)
	{
		this->m_EventManager->addObserver(this);
	}

	CollisionsManager::~CollisionsManager()
	{

	}

	void CollisionsManager::onNotify(Event event, void* pValue)
	{
		if (event == PLAYER_WALK)
		{
			Event blockEvent = (this->isColliding(*static_cast<SDL_Rect*>(pValue))) ? PLAYER_BLOCKED : PLAYER_NOT_BLOCKED;
			this->m_EventManager->notify(blockEvent, new std::string("player_collides"));
		}
	}

	bool CollisionsManager::isColliding(SDL_Rect target)
	{
		bool blocked = false;

		for (auto& collision : this->m_Collisions) {
			if (target.x <= collision.x + collision.w &&
				target.x + target.w >= collision.x &&
				target.y < collision.y + collision.h &&
				target.h + target.y >= collision.y) {
				blocked = true;
				break;
			}
		}

		return blocked;
	}

} }