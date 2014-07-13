#pragma once
#include "Component.h"
#include "RenderingSystem.h"
#include "Mesh.h"

class RenderComponent:public Component
{
public:
	RenderComponent();
	~RenderComponent();

	virtual void Start();
	virtual void Sleep();

	Mesh* GetMesh();
	bool IsCastingShadows();
	bool IsReceivingShadows();

private:
	RenderingSystem* m_RenderingSystem;

	Mesh* m_Mesh;
	bool m_CastShadows;
	bool m_ReceiveShadows;
};

