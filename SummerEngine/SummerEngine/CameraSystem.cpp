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
	Renderer* t_Renderer = t_Renderer->GetInstance();
	int numOfActiveCamneras = m_ActiveComponents.size();
	if (m_Changed)
	{
		std::vector<D3D11_VIEWPORT> t_Viewports;
		
		for (std::list<Component*>::iterator it = m_ActiveComponents.begin(); it != m_ActiveComponents.end(); it++)
		{
			t_Viewports.push_back(((CameraComponent*)(*it))->GetViewport());
			
		}
		t_Renderer->SetViewports(t_Viewports);
		m_Changed = false;
	}

	std::vector<Renderer::CameraStruct> t_CameraMatrices;

	for (std::list<Component*>::iterator it = m_ActiveComponents.begin(); it != m_ActiveComponents.end(); it++)
	{
		Renderer::CameraStruct t_NewStruct;
		CameraComponent* t_Camera = (CameraComponent*)(*it);

		t_NewStruct.Proj = t_Camera->GetProj();
		t_NewStruct.View = t_Camera->GetView();
		//t_NewStruct.ViewProj = t_Camera->GetViewProj();
		t_CameraMatrices.push_back(t_NewStruct);
	}
	t_Renderer->SetCameras(t_CameraMatrices);
}

void CameraSystem::Destroy()
{

}

void CameraSystem::Register(Component* p_Component)
{
	System::Register(p_Component);
	m_Changed = true;
}

void CameraSystem::Unregister(Component* p_Component)
{
	System::Unregister(p_Component);
	m_Changed = true;
}

void CameraSystem::EnableComponent(Component* p_Component)
{
	System::EnableComponent(p_Component);
	m_Changed = true;
}

void CameraSystem::DisableComponent(Component* p_Component)
{
	System::DisableComponent(p_Component);
	m_Changed = true;
}