#pragma once
#include "System.h"
#include "../Graphics/GraphicToolbox.h"

//handles all components that wants to make use of inputs
//TODO: Should handle the CPU culling of objects, and send the ones to draw to the engine

class RenderingSystem : public System
{
public:
	RenderingSystem();
	~RenderingSystem();

	bool Update();

private:
	void SortComponents();
	
	//we use a list of the objects we want to send to the engine, and add/remove to this when we add/remove components
	std::vector<SGEngine::RenderObject> m_Opaque;
	std::vector<SGEngine::RenderObject> m_Transparent;
};

