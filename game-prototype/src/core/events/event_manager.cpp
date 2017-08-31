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
		this->m_Observers.push_back(observer);
	}

	void EventManager::removeObserver(Observer* observer)
	{
		auto it = std::find(this->m_Observers.begin(), this->m_Observers.end(), observer);
		if (it != this->m_Observers.end())
		{
			this->m_Observers.erase(it);
		}
	}

	void EventManager::notify(Event event)
	{
		for (auto& observer : this->m_Observers)
		{
			observer->onNotify(event);
		}
	}

	void EventManager::notify(Event event, std::string data)
	{
		for (auto& observer : this->m_Observers)
		{
			observer->onNotify(event, data);
		}
	}

	void EventManager::notify(Event event, std::string data, int data2, int data3)
	{
		for (auto& observer : this->m_Observers)
		{
			observer->onNotify(event, data, data2, data3);
		}
	}

	void EventManager::notify(Event event, glm::vec4 data)
	{
		for (auto& observer : this->m_Observers)
		{
			observer->onNotify(event, data);
		}
	}

} }