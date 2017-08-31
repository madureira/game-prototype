#pragma once

#include <vector>
#include "../entities/trigger.h"
#include "../events/observer.h"
#include "../events/event_manager.h"

namespace core { namespace triggers {

	using namespace events;
	using namespace entities;

	class TriggerManager : public Observer
	{
	private:
		std::vector<Trigger*> m_Triggers;
		EventManager* m_EventManager;

	public:
		TriggerManager(std::vector<Trigger*> triggers, EventManager* eventManager);
		~TriggerManager();

		virtual void onNotify(Event event, void* pValue);
	};

} }