#include "RenderingComponent.h"
#include "../Systems/RenderingSystem.h"

RenderingComponent::RenderingComponent() : Component("RenderingComponent")
{
	RenderingSystem* m_Sys = m_Sys->GetInstance();

	m_Sys->Register(this);
	m_IsTransparent = false;
	m_RenderObjectHandle = 0;
}

RenderingComponent::RenderingComponent(std::string p_Name) : Component(p_Name)
{
	RenderingSystem* m_Sys = m_Sys->GetInstance();

	m_Sys->Register(this);
	m_IsTransparent = false;
	m_RenderObjectHandle = 0;
}

RenderingComponent::~RenderingComponent()
{
	RenderingSystem* m_Sys = m_Sys->GetInstance();

	m_Sys->Unregister(this);
}

//should be called when enabled ? maybe same as constructor, could remove maybe
void RenderingComponent::Awake()
{
	
}

//start the component, to do the work its supposd to
void RenderingComponent::Start()
{

}

//pause the component
void RenderingComponent::Sleep()
{
	
}

//update component, called from systems
void RenderingComponent::Update()
{

}

//called when removing component
void RenderingComponent::Destroy()
{

}

void RenderingComponent::Enable()
{
	RenderingSystem* m_Sys = m_Sys->GetInstance();

	m_Sys->EnableComponent(this);
}

void RenderingComponent::Disable()
{
	RenderingSystem* m_Sys = m_Sys->GetInstance();

	m_Sys->DisableComponent(this);
}

void RenderingComponent::Create(bool p_IsTransparent, RenderObject p_RenderObject)
{
	RenderingSystem* m_Sys = m_Sys->GetInstance();

	m_Sys->AddObject(p_IsTransparent, p_RenderObject, this);
	m_IsTransparent = p_IsTransparent;
}


void RenderingComponent::SetMesh(MeshHandle p_MeshHandle)
{
	//m_MeshHandle = p_MeshHandle;
}

void RenderingComponent::SetMaterial(MaterialHandle p_MaterialHandle)
{
	//m_MaterialHandle = p_MaterialHandle;
}