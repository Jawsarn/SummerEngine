#include "CameraSystem.h"
#include "Renderer.h"
#include "CameraComponent.h"
#include "TransformComponent.h"
#include "Time.h"

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

void CameraSystem::Walk(int p_Amount)
{
	for (std::list<Component*>::iterator it = m_ActiveComponents.begin(); it != m_ActiveComponents.end(); it++)
	{
		Time* t_Time = t_Time->GetInstace();

		((TransformComponent*)(*it)->GetEntity()->GetTransformComponent())->Walk(t_Time->GetDeltaTime() * 200 * p_Amount);
	}
}

void CameraSystem::Strafe(int p_Amount)
{
	for (std::list<Component*>::iterator it = m_ActiveComponents.begin(); it != m_ActiveComponents.end(); it++)
	{
		Time* t_Time = t_Time->GetInstace();

		((TransformComponent*)(*it)->GetEntity()->GetTransformComponent())->Strafe(t_Time->GetDeltaTime() * 200 * p_Amount);
	}
}

void CameraSystem::HoverY(int p_Amount)
{
	for (std::list<Component*>::iterator it = m_ActiveComponents.begin(); it != m_ActiveComponents.end(); it++)
	{
		Time* t_Time = t_Time->GetInstace();

		((TransformComponent*)(*it)->GetEntity()->GetTransformComponent())->HoverY(t_Time->GetDeltaTime() * 200 * p_Amount);
	}
}

void CameraSystem::Pitch(float p_Dy)
{
	for (std::list<Component*>::iterator it = m_ActiveComponents.begin(); it != m_ActiveComponents.end(); it++)
	{
		((TransformComponent*)(*it)->GetEntity()->GetTransformComponent())->Pitch(p_Dy);
	}
}

void CameraSystem::RotateY(float p_Dx)
{
	for (std::list<Component*>::iterator it = m_ActiveComponents.begin(); it != m_ActiveComponents.end(); it++)
	{
		((TransformComponent*)(*it)->GetEntity()->GetTransformComponent())->RotateY(p_Dx);
	}
}