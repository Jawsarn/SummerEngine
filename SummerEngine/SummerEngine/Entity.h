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

	int GetID();

	void AddComponent(Component *p_Component);
	void SetParent(Entity *p_Parent);
	void AddChild(Entity* p_Child);

	Entity* GetParent();
	std::vector<Entity*> GetChildren();

	virtual bool Read(Stream &p_Stream);
	virtual bool Write(Stream &p_Stream);

protected:
	int m_EntityID;
	std::string m_Name;
	Entity* m_Parent;
	std::vector<Entity*> m_Children;

	std::vector<Component*> m_Components;
};

