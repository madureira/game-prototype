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

	void TriggerManager::onNotify(Event event, glm::vec4 data)
	{
		if (event == PLAYER_WALK)
		{
			for (auto& trigger : this->m_Triggers)
			{
				TRIGGER_EVENTS tEvent = trigger->getEvent(data.x, data.y, data.z, data.w);

				if (tEvent == ON_ENTER)
				{
					this->m_EventManager->notify(PLAYER_TRIGGER_ON, trigger->getName());
					break;
				}
			}
		}
	}

} }