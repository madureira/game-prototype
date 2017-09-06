#pragma once

#include <string>

namespace core { namespace utils {

	class StringUtils
	{
	public:
		static std::string getFolderFromPath(const std::string& path)
		{
			return path.substr(0, path.find_last_of("/\\")) + "/";
		}
	};

} }