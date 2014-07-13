#pragma once
#include "Component.h"
#include <vector>

class Entity
{
public:
	Entity();
	Entity(const Entity &p_Copy);
	Entity(const Entity &p_Copy, Entity* p_Parent);
	~Entity();
	void AddComponent(Component *p_Component);
	void SetParent(Entity *p_Parent);

	Entity* GetParent();
	std::vector<Entity*> GetChildren();

protected:
	int m_EntityID;
	Entity* m_Parent;
	std::vector<Entity*> m_Children;

	std::string m_Name; //not sure if needed
	std::vector<Component*> m_Components;
};

