#pragma once
#include "Component.h"
#include <list>


class Entity
{
public:
	Entity();
	~Entity();

private:
	int m_EntityID;
	std::list<Component> m_Components;
	std::string m_Name; //not sure if needed
};

