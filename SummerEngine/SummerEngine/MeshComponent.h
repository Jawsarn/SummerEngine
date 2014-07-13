#pragma once
#include "Component.h"
#include "Mesh.h"
class MeshComponent:public Component
{
public:
	MeshComponent();
	~MeshComponent();
	Mesh *mesh;
};

