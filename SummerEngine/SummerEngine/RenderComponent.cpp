#include "RenderComponent.h"


RenderComponent::RenderComponent()
{
	m_RenderingSystem = m_RenderingSystem->GetInstance();
}


RenderComponent::~RenderComponent()
{
}
