#include "CameraSystem.h"
#include "Renderer.h"
#include "CameraComponent.h"

CameraSystem* CameraSystem::m_Singleton = nullptr;

CameraSystem* CameraSystem::GetInstance()
{
	if (m_Singleton == nullptr)
	{
		m_Singleton = new CameraSystem();
	}
	return m_Singleton;
}

CameraSystem::CameraSystem()
{
}


CameraSystem::~CameraSystem()
{
}


void CameraSystem::Awake()
{

}

void CameraSystem::Start()
{

}

void CameraSystem::Update()
{
	if (m_Changed)
	{
		int numOfActiveCamneras = m_ActiveComponents.size();
		std::vector<D3D11_VIEWPORT> t_Viewports;
		
		for (std::list<Component*>::iterator it = m_ActiveComponents.begin(); it != m_ActiveComponents.end(); it++)
		{
			t_Viewports.push_back(((CameraComponent*)(*it))->GetViewport());
			
		}

		Renderer* t_Renderer = t_Renderer->GetInstance();
		t_Renderer->SetViewports(t_Viewports);
	}
}

void CameraSystem::Destroy()
{

}