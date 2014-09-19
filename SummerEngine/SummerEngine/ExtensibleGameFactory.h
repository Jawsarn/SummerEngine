#pragma once

#include "Entity.h"
#include <map>

/*factory where we can easely register and create new Entities and Component, we can register a set of an "orc" and then use this to create duplicates of that orc
NOTE: Entity is not fixed yet maybe. Depends on if the "saved" entity should be held in some place where the user can't destroy it, so the outcome of create wont differ and wont be removed*/

class ExtensibleGameFactory
{
public:
	typedef std::string ComponentType;

	typedef std::string ObjectType;

	static ExtensibleGameFactory* GetInstance();
	

	Entity* CreateEntity(ObjectType p_Type);
	Component* CreateComponent(ComponentType p_Type);

	void Register(Entity* p_Entity, ObjectType p_Type);
	void Unregister(ObjectType p_Type);

private:
	ExtensibleGameFactory();
	~ExtensibleGameFactory();

	static ExtensibleGameFactory* m_Singleton;

	typedef std::map<ObjectType, Entity*> EntityMap;
	
	
	EntityMap m_EntityMakers;
	//ComponentMap m_ComponentMakers;
};
