#include "DirectXGraphicEngine.h"
#include "../Utility/Logger.h"

void DirectXGraphicEngine::UseCamera(SGEngine::Camera p_Camera, UINT p_Slot)
{
	//if we're selection a viewport that exists
	if (m_View.size() >= p_Slot + 1)
	{
		m_View[p_Slot].camera = p_Camera;
	}
	else
	{
		Logger::Log("UseCamera was called on invalid camera slot", "RenderSystem", LoggerType::MSG_WARNING);
	}
	
}