#include "RenderingSystem.h"

RenderingSystem* RenderingSystem::m_Singleton = nullptr;

RenderingSystem* RenderingSystem::GetInstance()
{
	if (m_Singleton == nullptr)
	{
		m_Singleton = new RenderingSystem();
	}
	return m_Singleton;
}

RenderingSystem::RenderingSystem()
{
	m_Renderer = m_Renderer->GetInstance();
}

RenderingSystem::~RenderingSystem()
{
}

void RenderingSystem::Awake()
{

}

void RenderingSystem::Start()
{
	
}

void RenderingSystem::Update()
{
	//std::list<Entity*>* t_CulledEntities;

	m_Renderer->BeginRender();

	m_Renderer->RenderOpaque();

	m_Renderer->RenderTransparent();

	m_Renderer->EndRender();
}

void RenderingSystem::Destroy()
{

}