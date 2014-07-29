#include "RenderingSystem.h"
#include "RenderComponent.h"

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

	m_Renderer->RenderOpaque(&m_Opaque); //fix

	//m_Renderer->RenderShadowmaps(&m_Opaque);

	m_Renderer->ComputeDeferred();

	//m_Renderer->RenderTransparent();

	m_Renderer->EndRender();
}

void RenderingSystem::Destroy()
{

}

void RenderingSystem::Register(Component* p_Component)
{
	if (p_Component->IsEnabled())
	{
		RenderComponent* t_Component = (RenderComponent*)p_Component;
		int t_NumOfObjects = t_Component->GetNumOfObjects();

		for (int i = 0; i < t_NumOfObjects; i++)
		{
			Renderer::RenderObject* t_NewObject = new Renderer::RenderObject();
			t_NewObject->m_Component = p_Component;

			t_NewObject->BufferNum = i;

			m_Opaque.push_back(t_NewObject);
		}
	}
	System::Register(p_Component);
}

void RenderingSystem::Unregister(Component* p_Component)
{
	System::Unregister(p_Component);
}

void RenderingSystem::EnableComponent(Component* p_Component) //fix
{
	RenderComponent* t_Component = (RenderComponent*)p_Component;
	int t_NumOfObjects = t_Component->GetNumOfObjects();

	for (int i = 0; i < t_NumOfObjects; i++)
	{
		Renderer::RenderObject* t_NewObject = new Renderer::RenderObject();
		t_NewObject->m_Component = p_Component;
		t_NewObject->BufferNum = i;

		m_Opaque.push_back(t_NewObject);
	}

	System::EnableComponent(p_Component);
}

void RenderingSystem::DisableComponent(Component* p_Component)
{
	//m_Opaque.erase(); FIX
	System::DisableComponent(p_Component);
}

void RenderingSystem::UpdateComponent(Component* p_Component)
{
	RenderComponent* t_Component = (RenderComponent*)p_Component;
	int t_NewNumOfBuffers = t_Component->GetNumOfObjects();

	//loop and remove the objects, in case of them beein in wrong lists?
	for (std::vector<Renderer::RenderObject*>::iterator it = m_Opaque.begin(); it != m_Opaque.end(); it++)
	{
		if ((*it)->m_Component == p_Component)
		{
			it = m_Opaque.erase(it);
		}
	}
	

	//add the new in correct lists, currently only opaque
	for (int i = 0; i < t_NewNumOfBuffers; i++)
	{
		Renderer::RenderObject* t_NewObject = new Renderer::RenderObject();
		t_NewObject->m_Component = p_Component;
		t_NewObject->BufferNum = i;

		m_Opaque.push_back(t_NewObject);
	}
}