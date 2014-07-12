#include "RenderComponent.h"


RenderComponent::RenderComponent()
{
	m_RenderingSystem = m_RenderingSystem->GetInstance();
	m_RenderingSystem->Register(m_Entity);
}


RenderComponent::~RenderComponent()
{
	m_RenderingSystem->Unregister(m_Entity);
}
