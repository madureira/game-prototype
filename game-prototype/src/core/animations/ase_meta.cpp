#include "ase_meta.h"

namespace core { namespace ase {

	AseMeta::AseMeta(json &meta)
	{
		m_SpriteWidth = meta["size"]["w"];
		m_SpriteHeight = meta["size"]["h"];

		std::string image = meta["image"];
		std::string scale = meta["scale"];

		size_t found = image.find_last_of("/\\");
		m_SpriteName = image.substr(found + 1);
		m_Scale = std::stoi(scale.c_str());

		for (auto& frameTag : meta["frameTags"])
		{
			m_FrameTags.push_back(FrameTag(frameTag["name"], frameTag["from"], frameTag["to"], frameTag["direction"]));
		}
	}

	AseMeta::AseMeta()
	{

	}

	AseMeta::~AseMeta()
	{

	}

} }