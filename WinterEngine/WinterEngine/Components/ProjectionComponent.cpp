#include "ProjectionComponent.h"
#include "../Matrix/MatrixLibraryInterface.h"
#include "../Systems/RenderingSystem.h"

ProjectionComponent::ProjectionComponent() : Component("ProjectionComponent")
{
	m_IsOrthogonal = true;
	m_ProjMatrixHandle = 0;
}

ProjectionComponent::ProjectionComponent(std::string p_Name) : Component(p_Name)
{
	m_IsOrthogonal = true;
	m_ProjMatrixHandle = 0;
}


ProjectionComponent::~ProjectionComponent()
{
}

unsigned int ProjectionComponent::CreateCamera(FoVProjMatrix* p_FieldOfView, MatrixHandle p_MatrixHandle)
{
	MatrixLibraryInterface* t_Lib = t_Lib->GetInstance();

	m_ProjMatrixHandle = t_Lib->CreateMatrix(p_FieldOfView);
	m_IsOrthogonal = false;
	m_IsCamera = true;

	RenderingSystem* m_Sys = m_Sys->GetInstance();
	m_CameraHandle = m_Sys->AddCamera(p_MatrixHandle, m_ProjMatrixHandle, this);

	return m_ProjMatrixHandle;
}

unsigned int ProjectionComponent::CreateCamera(OrthoProjMatrix* p_FieldOfView, MatrixHandle p_MatrixHandle)
{
	MatrixLibraryInterface* t_Lib = t_Lib->GetInstance();

	m_ProjMatrixHandle = t_Lib->CreateMatrix(p_FieldOfView);
	m_IsOrthogonal = true;
	m_IsCamera = true;

	RenderingSystem* m_Sys = m_Sys->GetInstance();
	m_CameraHandle = m_Sys->AddCamera(p_MatrixHandle, m_ProjMatrixHandle, this);

	return m_ProjMatrixHandle;
}
bool ProjectionComponent::IsCamera()
{
	return m_IsCamera;
}
void ProjectionComponent::UseCamera()
{
	if (m_IsCamera)
	{
		RenderingSystem* m_Sys = m_Sys->GetInstance();
		m_Sys->UseCamera(m_CameraHandle);
	}
}