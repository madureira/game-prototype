#pragma once

#include <string>
#include <vector>
#include "observer.h"

namespace core { namespace events {

	class EventManager
	{
	private:
		std::vector<Observer*> m_Observers;

	public:
		EventManager();
		~EventManager();

		void addObserver(Observer* observer);
		void removeObserver(Observer* observer);
		void notify(const Entity& entity, Event event, void* pValue);
	};

} }