#include "RenderComponent.h"


RenderComponent::RenderComponent()
{
	
}

RenderComponent::~RenderComponent()
{
	
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