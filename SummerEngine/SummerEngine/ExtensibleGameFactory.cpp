#include "ExtensibleGameFactory.h"
#include "RenderComponent.h"
#include "TransformComponent.h"

ExtensibleGameFactory* ExtensibleGameFactory::m_Singleton = nullptr;

ExtensibleGameFactory* ExtensibleGameFactory::GetInstance()
{
	if (m_Singleton == nullptr)
	{
		m_Singleton = new ExtensibleGameFactory();
	}
	return m_Singleton;
}

ExtensibleGameFactory::ExtensibleGameFactory()
{
}


ExtensibleGameFactory::~ExtensibleGameFactory()
{
}

Entity* ExtensibleGameFactory::CreateEntity(ObjectType p_Type)
{
	EntityMap::iterator it = m_EntityMakers.find(p_Type);
	if (it == m_EntityMakers.end())
	{
		return nullptr;
	}

	return new Entity(*it->second);
}

Component* ExtensibleGameFactory::CreateComponent(ComponentType p_Type) //could change this but that'll take lot of time, and is not really needed for this small project
{
	if (p_Type == "Component")
	{
		return new Component();
	}
	else if (p_Type == "RenderComponent")
	{
		return new RenderComponent();
	}
	else if (p_Type == "TransformComponent")
	{
		return new TransformComponent();
	}
	else
	{
		return nullptr;
	}
}

void ExtensibleGameFactory::Register(Entity* p_Entity, ObjectType p_Type)
{
	m_EntityMakers[p_Type] = p_Entity;
}

void ExtensibleGameFactory::Unregister(ObjectType p_Type)
{
	m_EntityMakers.erase(p_Type);
}