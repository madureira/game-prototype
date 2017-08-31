#pragma once

#include <string>
#include <glm/vec4.hpp>
#include "event.h"

namespace core { namespace events {

	class Observer
	{
	public:
		virtual ~Observer() {}

		virtual void onNotify(Event event) {};
		virtual void onNotify(Event event, std::string data) {};
		virtual void onNotify(Event event, std::string data, int data2, int data3) {};
		virtual void onNotify(Event event, glm::vec4 data) {};
	};

} }