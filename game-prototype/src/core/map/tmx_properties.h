#pragma once

#include <vector>
#include <string>
#include "../libs/tinyxml2.h"

namespace core { namespace tmx {

	using namespace tinyxml2;

	struct TmxProperty
	{
		std::string name;
		std::string type;
		std::string value;

		TmxProperty() {}
		TmxProperty(std::string a, std::string b, std::string c)
			: name(a), type(b), value(c) {}
	};

	class TmxProperties
	{
	private:
		std::vector<TmxProperty> m_Properties;

	public:
		TmxProperties() {}
		TmxProperties(XMLElement* propertyElem);
		~TmxProperties();

		TmxProperty getProperty(std::string name);
	};

} }