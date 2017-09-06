#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include "../../libs/json.hpp"
#include "../animation.h"
#include "ase_frames.h"
#include "ase_meta.h"

namespace core { namespace ase {

	using json = nlohmann::json;
	using namespace animations;

	class AseParse
	{
	private:
		std::string m_SpritePath;
		std::vector<Animation> m_Animations;
		std::vector<AseFrames> m_Frames;
		AseMeta m_Meta;

	public:
		AseParse(std::string jsonPath);
		~AseParse();
		inline std::vector<Animation> getAnimations() const { return m_Animations; }
		inline std::string getSpritePath() const { return m_SpritePath; }

	private:
		void parseFrames(json &jStream);
		void parseMeta(json &jStream, std::string directoryPath);
		void buildAnimations();
		std::string getPathFolder(const std::string& filePath);
	};

} }