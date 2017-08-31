#include "event_manager.h"

namespace core { namespace events {

	EventManager::EventManager()
	{

	}

	EventManager::~EventManager()
	{

	}

	void EventManager::addObserver(Observer* observer)
	{
		m_Observers.push_back(observer);
	}

	void EventManager::removeObserver(Observer* observer)
	{
		auto it = std::find(m_Observers.begin(), m_Observers.end(), observer);
		if (it != m_Observers.end())
		{
			m_Observers.erase(it);
		}
	}

	void EventManager::notify(Event event, void* pValue)
	{
		for (auto& observer : m_Observers)
		{
			observer->onNotify(event, pValue);
		}
	}

} }