#include "ExtensibleGameFactory.h"
#include "RenderComponent.h"
#include "TransformComponent.h"

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

Component* ExtensibleGameFactory::CreateComponent(ComponentType p_Type)
{
	switch (p_Type)
	{
	case NORMAL:
		return new Component();
		break;
	case RENDERER:
		return new RenderComponent();
		break;
	case TRANSFORM:
		return new TransformComponent();
		break;
	default:
		break;
	}

	return nullptr;
}

void ExtensibleGameFactory::Register(Entity* p_Entity, ObjectType p_Type)
{
	m_EntityMakers[p_Type] = p_Entity;
}

void ExtensibleGameFactory::Unregister(ObjectType p_Type)
{
	m_EntityMakers.erase(p_Type);
}