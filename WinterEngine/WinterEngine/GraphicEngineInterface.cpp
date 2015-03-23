#include "GraphicEngineInterface.h"
#include "DirectXGraphicEngine.h"
GraphicEngineInterface* GraphicEngineInterface::m_GraphicEngine = nullptr;

GraphicEngineInterface* GraphicEngineInterface::GetInstance()
{
	//return directxEngine, this is where we set the engine, I think this will work
	//if we add openGL engine, we might have some pre-compile defines that tells us what we include?
	if (m_GraphicEngine == nullptr)
		m_GraphicEngine = new DirectXGraphicEngine();
	return m_GraphicEngine;
}

GraphicEngineInterface::GraphicEngineInterface()
{
}


GraphicEngineInterface::~GraphicEngineInterface()
{
}
