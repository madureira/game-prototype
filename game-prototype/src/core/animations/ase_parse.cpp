#include "ase_parse.h"

namespace core { namespace ase {

	AseParse::AseParse(std::string jsonPath)
	{
		json jStream;
		std::ifstream jsonFile(jsonPath);

		if (jsonFile.is_open())
		{
			jsonFile >> jStream;
			
			if (!jStream.is_null())
			{
				if (jStream.find("frames") != jStream.end())
				{
					parseFrames(jStream);
				}

				if (jStream.find("meta") != jStream.end())
				{
					parseMeta(jStream);
				}

				buildAnimations();
			}
		}
		else
		{
			std::cout << "Cannot open animations from file: " << jsonPath << std::endl;
		}

		jsonFile.close();
	}

	AseParse::~AseParse()
	{

	}

	void AseParse::parseFrames(json &jStream)
	{
		for (auto &frame : jStream.find("frames").value())
		{
			m_Frames.push_back(AseFrames(frame));
		}
	}

	void AseParse::parseMeta(json &jStream)
	{
		m_Meta = AseMeta(jStream.find("meta").value());
		m_SpriteName = m_Meta.getSpriteName();
	}

	void AseParse::buildAnimations()
	{
		for (auto& tag : m_Meta.getFrameTags())
		{
			std::vector<Frame> animationFrames;

			int i = 0;
			for (auto& frame : m_Frames)
			{
				if (i >= tag.from && i <= tag.to)
				{
					animationFrames.push_back(Frame(frame.getFrame(), frame.getDuration(), frame.isRotated()));
				}
				i++;
			}
			m_Animations.push_back(Animation(tag.name, m_Meta.getWidth(), m_Meta.getHeight(), animationFrames));
		}
	}

} }
