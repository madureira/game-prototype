#include "ase_frames.h"

namespace core { namespace ase {

	AseFrames::AseFrames(json &frame)
	{
		m_Frame = { frame["frame"]["x"] , frame["frame"]["y"], frame["frame"]["w"], frame["frame"]["h"] };
		m_Rotated = frame["rotated"];
		m_Duration = frame["duration"];
	}


	AseFrames::~AseFrames()
	{

	}

} }