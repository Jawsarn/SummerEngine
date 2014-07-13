#include "Entity.h"


Entity::Entity()
{
	m_Parent = nullptr;
}


Entity::~Entity()
{
}

void Entity::AddComponent( Component *p_Component )
{
	m_Components.push_back(p_Component);
}

void Entity::SetParent(Entity *p_parent)
{
	m_Parent = p_parent;
}

std::list<Entity> Entity::GetChildren()
{
	return m_Children;
}

Entity* Entity::GetParent()
{
	return m_Parent;
}
