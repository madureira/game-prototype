#include "tmx_tile.h"

namespace core { namespace tmx {

	TmxTile::TmxTile(XMLElement* tileElem)
	{
		this->m_Gid = tileElem->IntAttribute("gid");
	}

	TmxTile::~TmxTile()
	{

	}

} }