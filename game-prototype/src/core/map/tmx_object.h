#pragma once

#include <vector>
#include <string>
#include "../libs/tinyxml2.h"
#include "tmx_polyline.h"
#include "tmx_properties.h"

namespace core { namespace tmx {

	using namespace tinyxml2;

	class TmxObject {
	private:
		int m_Id;
		int m_X;
		int m_Y;
		int m_Width;
		int m_Height;
		int m_Velocity;
		TmxPolyline m_Polyline;
		TmxProperties m_Properties;

	public:
		TmxObject(XMLElement* objectElem);
		~TmxObject();

		int getId() const { return m_Id; }
		int getX() const { return m_X; }
		int getY() const { return m_Y; }
		int getWidth() const { return m_Width; }
		int getHeight() const { return m_Height; }
		int getVelocity() const { return m_Velocity; }
		TmxPolyline getPolyline() const { return m_Polyline; }
		TmxProperties getProperties() const { return m_Properties; }
	};

} }