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
		std::string m_Name;
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

		inline int getId() const { return m_Id; }
		inline std::string getName() const { return m_Name; }
		inline int getX() const { return m_X; }
		inline int getY() const { return m_Y; }
		inline int getWidth() const { return m_Width; }
		inline int getHeight() const { return m_Height; }
		inline int getVelocity() const { return m_Velocity; }
		inline TmxPolyline getPolyline() const { return m_Polyline; }
		inline TmxProperties getProperties() const { return m_Properties; }
	};

} }