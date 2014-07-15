#pragma once

#include "Entity.h"
#include <map>



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
