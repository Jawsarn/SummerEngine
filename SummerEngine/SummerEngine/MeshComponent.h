#pragma once
#include "Component.h"
#include "Mesh.h"

class MeshComponent:public Component
{
public:
	MeshComponent();
	~MeshComponent();

	Mesh* GetMesh();

	bool IsCastShadows();
	bool IsReceiveShadows();
	
private:
	Mesh *m_Mesh;
	bool m_CastShadows;
	bool m_ReceiveShadows;
};

