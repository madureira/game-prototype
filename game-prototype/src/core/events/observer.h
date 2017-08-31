#pragma once

#include <string>
#include "../entities/entity.h"
#include "event.h"

namespace core { namespace events {

	using namespace entities;

	class Observer
	{
	public:
		virtual ~Observer() {}
		
		virtual void onNotify(const Entity& entity, Event event, void* pValue) = 0;
	};

} }