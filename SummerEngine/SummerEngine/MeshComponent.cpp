#include "MeshComponent.h"


MeshComponent::MeshComponent()
{
}


MeshComponent::~MeshComponent()
{
}

Mesh* MeshComponent::GetMesh()
{
	return m_Mesh;
}

bool MeshComponent::IsCastShadows()
{
	return m_CastShadows;
}

bool MeshComponent::IsReceiveShadows()
{
	return m_ReceiveShadows;
}