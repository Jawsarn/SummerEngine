#pragma once
#include "Component.h"
#include <list>


class Entity
{
public:
	Entity();
	~Entity();
	void AddComponent(Component &p_Component);

protected:
	int m_EntityID;
	std::string m_Name; //not sure if needed
	std::list<Component> m_Components;
};

