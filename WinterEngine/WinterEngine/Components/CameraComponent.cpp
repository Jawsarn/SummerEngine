#include "CameraComponent.h"
#include "../Matrix/MatrixLibraryInterface.h"
#include "../Systems/RenderingSystem.h"

CameraComponent::CameraComponent() : Component("CameraComponent")
{
	m_IsOrthogonal = true;
	m_ProjMatrixHandle = 0;
}

CameraComponent::CameraComponent(std::string p_Name) : Component(p_Name)
{
	m_IsOrthogonal = true;
	m_ProjMatrixHandle = 0;
}


CameraComponent::~CameraComponent()
{
}

unsigned int CameraComponent::CreateCamera(FoVProjMatrix* p_FieldOfView, MatrixHandle p_MatrixHandle)
{
	MatrixLibraryInterface* t_Lib = t_Lib->GetInstance();

	m_ProjMatrixHandle = t_Lib->CreateMatrix(p_FieldOfView);
	m_IsOrthogonal = false;
	m_IsCamera = true;

	RenderingSystem* m_Sys = m_Sys->GetInstance();
	m_CameraHandle = m_Sys->AddCamera(p_MatrixHandle, m_ProjMatrixHandle, this);

	return m_ProjMatrixHandle;
}

unsigned int CameraComponent::CreateCamera(OrthoProjMatrix* p_FieldOfView, MatrixHandle p_MatrixHandle)
{
	MatrixLibraryInterface* t_Lib = t_Lib->GetInstance();

	m_ProjMatrixHandle = t_Lib->CreateMatrix(p_FieldOfView);
	m_IsOrthogonal = true;
	m_IsCamera = true;

	RenderingSystem* m_Sys = m_Sys->GetInstance();
	m_CameraHandle = m_Sys->AddCamera(p_MatrixHandle, m_ProjMatrixHandle, this);

	return m_ProjMatrixHandle;
}
bool CameraComponent::IsCamera()
{
	return m_IsCamera;
}
void CameraComponent::UseCamera()
{
	if (m_IsCamera)
	{
		RenderingSystem* m_Sys = m_Sys->GetInstance();
		m_Sys->UseCamera(m_CameraHandle);
	}
}