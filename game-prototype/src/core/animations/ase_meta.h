#pragma once

#include <string>
#include <vector>
#include "../libs/json.hpp"

namespace core { namespace ase {

	using json = nlohmann::json;

	struct FrameTag {
		std::string name;
		int from;
		int to;
		std::string direction;

		FrameTag(std::string n, int f, int t, std::string d) {
			name = n;
			from = f;
			to = t;
			direction = d;
		}

		FrameTag() : name(""), from(0), to(0), direction("") {}
	};

	class AseMeta
	{
	private:
		std::string m_SpriteName;
		int m_SpriteWidth;
		int m_SpriteHeight;
		int m_Scale;
		std::vector<FrameTag> m_FrameTags;

	public:
		AseMeta(json &meta);
		AseMeta();
		~AseMeta();

		std::string getSpriteName() const { return m_SpriteName; }
		int getWidth() const { return m_SpriteWidth; }
		int getHeight() const { return m_SpriteHeight; }
		int getScale() const { return m_Scale; }
		std::vector<FrameTag> getFrameTags() const { return m_FrameTags; }
	};

} }