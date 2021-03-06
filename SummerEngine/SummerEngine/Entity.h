#pragma once
#include "Serializable.h"
#include "Component.h"
#include <vector>

/*Basic entity with parent children, and components*/

class Entity:Serializable
{
public:
	Entity();
	Entity(std::string p_Name);
	Entity(const Entity &p_Copy);
	//Entity(const Entity &p_Copy, Entity* p_Parent);
	~Entity();

	int GetID();

	void AddComponent(Component *p_Component);
	void SetParent(Entity *p_Parent);
	void AddChild(Entity* p_Child);

	Entity* GetParent();
	std::vector<Entity*> GetChildren();

	Component* GetTransformComponent();

	virtual bool Read(Stream &p_Stream);
	virtual bool Write(Stream &p_Stream);
	virtual void Fixup();

	std::string GetName() const;

private:
	void Initialize(const Entity &p_Copy);

protected:
	int m_EntityID;
	std::string m_Name;
	Entity* m_Parent;
	std::vector<Entity*> m_Children;

	Component* m_TransformComponent;

	std::vector<Component*> m_Components;
};

