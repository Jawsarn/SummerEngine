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
	VertexHandle m_VertexBufferID;
	IndexHandle m_IndexBufferID;
	UINT m_StartVertex, m_EndVertex, m_StartIndex, m_EndIndex;
	MaterialHandle m_MaterialID;
};


