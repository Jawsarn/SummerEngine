#include "Entity.h"


Entity::Entity()
{
	m_Parent = nullptr;
}

Entity::Entity(const Entity &p_Copy)
{
	int t_NumOfComponents = p_Copy.m_Components.size();

	for (int i = 0; i < t_NumOfComponents; i++)
	{
		this->m_Components.push_back(new Component(*p_Copy.m_Components[i]));
	}

	this->m_EntityID = p_Copy.m_EntityID; //not sure if ID should follow? maybe not..
	this->m_Name = p_Copy.m_Name;
	this->m_Parent = nullptr;

	int t_NumOfChildren = p_Copy.m_Children.size();

	for (int i = 0; i < t_NumOfChildren; i++)
	{
		this->m_Children.push_back(new Entity(*p_Copy.m_Children[i], this));
	}
}

Entity::Entity(const Entity &p_Copy, Entity* parent)
{
	int t_NumOfComponents = p_Copy.m_Components.size();

	for (int i = 0; i < t_NumOfComponents; i++)
	{
		this->m_Components.push_back(new Component(*p_Copy.m_Components[i]));
	}

	this->m_EntityID = p_Copy.m_EntityID; //not sure if ID should follow? maybe not..
	this->m_Name = p_Copy.m_Name;
	this->m_Parent = parent;

	int t_NumOfChildren = p_Copy.m_Children.size();

	for (int i = 0; i < t_NumOfChildren; i++)
	{
		this->m_Children.push_back(new Entity(*p_Copy.m_Children[i], this));
	}
}

void CopyConstruct()
{

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
