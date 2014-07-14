#pragma once
#include "Serializable.h"
#include "Component.h"
#include <vector>

class Entity:Serializable
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

	virtual bool Read();
	virtual bool Write();

protected:
	int m_EntityID;
	Entity* m_Parent;
	std::vector<Entity*> m_Children;

	std::string m_Name; //not sure if needed
	std::vector<Component*> m_Components;
};

