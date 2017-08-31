#pragma once

#include <string>
#include <glm/vec4.hpp>
#include "event.h"

namespace core { namespace events {

	class Observer
	{
	public:
		virtual ~Observer() {}

		virtual void onNotify(Event event) = 0;
		virtual void onNotify(Event event, std::string data) = 0;
		virtual void onNotify(Event event, glm::vec4 data) = 0;
	};

} }