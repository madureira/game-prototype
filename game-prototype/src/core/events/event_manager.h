#pragma once

#include <algorithm>
#include <string>
#include <vector>
#include <glm/vec4.hpp>
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

		void notify(Event event);
		void notify(Event event, std::string data);
		void notify(Event event, std::string data, int data2, int data3);
		void notify(Event event, glm::vec4 data);
	};

} }
