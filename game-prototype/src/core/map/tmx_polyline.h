#pragma once

#include <vector>
#include <string>
#include <cstdlib> 
#include "../libs/tinyxml2.h"

namespace core { namespace tmx {

	using namespace tinyxml2;

	struct TmxPoint {
		int x;
		int y;
	};

	class TmxPolyline {
	private:
		std::vector<TmxPoint> m_Points;

	public:
		TmxPolyline() {}
		TmxPolyline(XMLElement* polylineElem, int x, int y);
		~TmxPolyline();

		std::vector<TmxPoint> getPoints() const { return m_Points; };
	};

} }