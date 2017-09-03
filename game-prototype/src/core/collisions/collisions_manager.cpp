#include "collisions_manager.h"

namespace core { namespace collisions {

	CollisionsManager::CollisionsManager(std::vector<SDL_Rect> collisions, EventManager* eventManager)
		: m_Collisions(collisions), m_EventManager(eventManager)
	{
		this->m_EventManager->addObserver(this);
	}

	CollisionsManager::~CollisionsManager()
	{
		m_Collisions.clear();
	}

	void CollisionsManager::onNotify(Event event, glm::vec4 data)
	{
		if (event == PLAYER_MOVE)
		{
			this->m_EventManager->notify((this->isColliding(data)) ? PLAYER_BLOCKED : PLAYER_NOT_BLOCKED);
		}
	}

	bool CollisionsManager::isColliding(glm::vec4 target)
	{
		bool blocked = false;

		for (auto& collision : this->m_Collisions) {
			if (target.x <= collision.x + collision.w &&
				target.y < collision.y + collision.h &&
				target.x + target.z >= collision.x &&
				target.y + target.w >= collision.y)
			{
				blocked = true;
				break;
			}
		}

		return blocked;
	}

} }