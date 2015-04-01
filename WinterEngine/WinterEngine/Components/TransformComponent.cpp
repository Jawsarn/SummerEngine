#include "TransformComponent.h"
#include "../Matrix/MatrixLibraryInterface.h"
//TODO:: Transform compnoent, not sure where I want the info, but I want it to be XMFLOAT4X4 if we're using windows, which puts me to the mood that we want some sort of interface to it, where
//the graphic and physics(?) engine can work around to get the directx values directly. This because the directX values can compute on the graphics drive in a nice way, and we can upload matrixes to
//graphic card diretly for drawing.

TransformComponent::TransformComponent() : Component("TransformComponent")
{
	m_MatrixHandle = 0;
}

TransformComponent::TransformComponent(std::string p_Name) : Component(p_Name)
{
	m_MatrixHandle = 0;
}


TransformComponent::~TransformComponent()
{
}

unsigned int TransformComponent::Create(Matrix* p_Matrix)
{
	MatrixLibraryInterface* t_Lib = t_Lib->GetInstance();

	m_MatrixHandle = t_Lib->CreateMatrix(p_Matrix);

	return m_MatrixHandle;
}