#pragma once

#include "../libs/tinyxml2.h"

namespace core { namespace tmx {

	using namespace tinyxml2;

	class TmxTile {
	private:
		int m_Gid;

	public:
		TmxTile(XMLElement* tileElem);
		~TmxTile();

		inline int getGid() const { return m_Gid; }
	};

} }