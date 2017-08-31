#include "trigger_manager.h"

namespace core { namespace triggers {

	TriggerManager::TriggerManager(std::vector<Trigger*> triggers, EventManager* eventManager)
		: m_Triggers(triggers), m_EventManager(eventManager)
	{
		this->m_EventManager->addObserver(this);
	}

	TriggerManager::~TriggerManager()
	{

	}

	void TriggerManager::onNotify(const Entity& entity, Event event, void* pValue)
	{
		if (event == PLAYER_WALK)
		{
			SDL_Rect* playerBox = static_cast<SDL_Rect*>(pValue);

			for (auto& trigger : this->m_Triggers)
			{
				TRIGGER_EVENTS tEvent = trigger->getEvent(playerBox->x, playerBox->y, playerBox->w, playerBox->h);

				if (tEvent == ON_ENTER)
				{
					void *vp = static_cast<void*>(new std::string("enter_door"));
					this->m_EventManager->notify(*trigger, PLAYER_TRIGGER_ON, vp);
					break;
				}
			}
		}
	}

} }