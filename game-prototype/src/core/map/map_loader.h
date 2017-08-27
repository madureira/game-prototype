#pragma once

#include <vector>
#include <string>
#include "../libs/tinyxml2.h"
#include "tmx_map.h"
#include "level.h"

namespace core { namespace tmx {

	using namespace tinyxml2;

	class MapLoader {
	public:
		MapLoader();
		~MapLoader();
		Level parse(const char* filePath);
	};

} }