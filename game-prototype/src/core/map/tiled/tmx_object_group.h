#pragma once

#include <vector>
#include <string>
#include "../../libs/tinyxml2.h"
#include "tmx_object.h"

namespace core { namespace tmx {

	using namespace tinyxml2;

	class TmxObjectGroup {
	private:
		std::string m_Name;
		std::vector<TmxObject> m_Objects;

	public:
		TmxObjectGroup(XMLElement* objectGroupElem);
		~TmxObjectGroup();

		std::string getName() const { return m_Name; }
		std::vector<TmxObject> getObjects() const { return m_Objects; }
	};

} }