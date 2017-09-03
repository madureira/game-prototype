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
					this->parseFrames(jStream);
				}

				if (jStream.find("meta") != jStream.end())
				{
					this->parseMeta(jStream);
				}

				this->buildAnimations();
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
			this->m_Frames.push_back(AseFrames(frame));
		}
	}

	void AseParse::parseMeta(json &jStream)
	{
		this->m_Meta = AseMeta(jStream.find("meta").value());
		this->m_SpriteName = this->m_Meta.getSpriteName();
	}

	void AseParse::buildAnimations()
	{
		for (auto& tag : this->m_Meta.getFrameTags())
		{
			std::vector<Frame> animationFrames;

			int i = 0;
			for (auto& frame : this->m_Frames)
			{
				if (i >= tag.from && i <= tag.to)
				{
					animationFrames.push_back(Frame(frame.getFrame(), frame.getDuration(), frame.isRotated()));
				}
				i++;
			}
			this->m_Animations.push_back(Animation(tag.name, this->m_Meta.getWidth(), this->m_Meta.getHeight(), animationFrames));
		}
	}

} }
