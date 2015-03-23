#pragma once
#include "Component.h"
#include "GraphicEngineInterface.h"

using namespace SGEngine;

class RenderingComponent : public Component
{
public:
	RenderingComponent();
	~RenderingComponent();


private:
	bool m_IsTransparent;
	MeshHandle* m_MeshHandle;
	UINT m_StartIndex, m_EndIndex;
	MaterialHandle m_MaterialID;
};


