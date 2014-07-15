#pragma once

#include "Entity.h"
#include <map>



class ExtensibleGameFactory
{
public:
	enum ComponentType
	{
		NORMAL,
		RENDERER,
		TRANSFORM
	};
	typedef std::string ObjectType;


	ExtensibleGameFactory();
	~ExtensibleGameFactory();

	Entity* CreateEntity(ObjectType p_Type);
	Component* CreateComponent(ComponentType p_Type);

	void Register(Entity* p_Entity, ObjectType p_Type);
	void Unregister(ObjectType p_Type);

private:
	typedef std::map<ObjectType, Entity*> EntityMap;
	
	EntityMap m_EntityMakers;
	//ComponentMap m_ComponentMakers;
};
