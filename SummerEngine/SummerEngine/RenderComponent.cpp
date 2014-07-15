#include "RenderComponent.h"


RenderComponent::RenderComponent() : Component("RenderComponent")
{
	
}

RenderComponent::RenderComponent(std::string p_Name) :Component(p_Name)
{

}

RenderComponent::~RenderComponent()
{
	
}

Mesh* RenderComponent::GetMesh()
{
	return m_Mesh;
}

bool RenderComponent::IsCastingShadows()
{
	return m_CastShadows;
}

bool RenderComponent::IsReceivingShadows()
{
	return m_ReceiveShadows;
}

void RenderComponent::Start()
{
	m_RenderingSystem = m_RenderingSystem->GetInstance();
	m_RenderingSystem->Register(m_Entity);
}

void RenderComponent::Sleep()
{
	m_RenderingSystem->Unregister(m_Entity);
}

bool RenderComponent::Read(Stream &p_Stream)
{
	return true;
}
bool RenderComponent::Write(Stream &p_Stream)
{
	return true;
}