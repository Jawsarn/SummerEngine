#include "Entity.h"


Entity::Entity()
{
}


Entity::~Entity()
{
}

void Entity::AddComponent(Component* p_Component)
{
	m_Components.push_back(p_Component);
}