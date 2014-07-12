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

}

void RenderingSystem::Destroy()
{

}