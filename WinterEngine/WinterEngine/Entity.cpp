#include "Entity.h"


Entity::Entity()
{
	m_Name = "DefaultEntity";
}

Entity::Entity(std::string p_Name)
{
	m_Name = p_Name;
}



Entity::~Entity()
{
}

void Entity::AddComponent(Component* p_Component)
{
	m_Components.push_back(p_Component);
	p_Component->SetEntity(this);
}

void Entity::AddComponents( Component** p_Components, unsigned int p_NumComponents )
{
	for( unsigned int i = 0; i < p_NumComponents; i++ )
		AddComponent( p_Components[i] );
}

