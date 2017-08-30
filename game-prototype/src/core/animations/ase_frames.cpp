#include "ase_frames.h"

namespace core { namespace ase {

	AseFrames::AseFrames(json &frame)
	{
		this->m_Frame = { frame["frame"]["x"] , frame["frame"]["y"], frame["frame"]["w"], frame["frame"]["h"] };
		this->m_Rotated = frame["rotated"];
		this->m_Duration = frame["duration"];
	}


	AseFrames::~AseFrames()
	{

	}

} }