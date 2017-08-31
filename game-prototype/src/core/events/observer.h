#pragma once

#include <string>
#include "event.h"

namespace core { namespace events {

	class Observer
	{
	public:
		virtual ~Observer() {}
		
		virtual void onNotify(Event event, void* pValue) = 0;
	};

} }