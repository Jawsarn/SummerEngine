#include <vector>
#include "Components/Component.h"

#pragma once
class Entity
{
public:
	Entity();
	Entity(std::string p_Name);
	~Entity();

	std::vector<Component*>* GetComponentList() { return &m_Components; }

	std::string GetName() const { return m_Name; }
	void AddComponent(Component* p_Component);

private:
	//name and ID
	std::string m_Name;
	int m_ID;

	//herarchy
	Entity* m_Parent;
	std::vector<Entity*> m_Children;

	//components
	std::vector<Component*> m_Components;

public:
	int GetID();
};

