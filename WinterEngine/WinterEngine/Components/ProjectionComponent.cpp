#include "ProjectionComponent.h"
#include "../Matrix/MatrixLibraryInterface.h"

ProjectionComponent::ProjectionComponent() : Component("ProjectionComponent")
{
}

ProjectionComponent::ProjectionComponent(std::string p_Name) : Component(p_Name)
{
}


ProjectionComponent::~ProjectionComponent()
{
}

void ProjectionComponent::Create(FoVProjMatrix* p_FieldOfView)
{
	MatrixLibraryInterface* t_Lib = t_Lib->GetInstance();

	m_ProjMatrixHandle = t_Lib->CreateMatrix(p_FieldOfView);
	m_IsEnabled = false;
}

void ProjectionComponent::Create(OrthoProjMatrix* p_FieldOfView)
{
	MatrixLibraryInterface* t_Lib = t_Lib->GetInstance();

	m_ProjMatrixHandle = t_Lib->CreateMatrix(p_FieldOfView);
	m_IsEnabled = true;
}