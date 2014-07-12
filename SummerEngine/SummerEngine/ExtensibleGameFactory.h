#pragma once
#include "Entity.h"
#include "FactoryMaker.h"
#include <map>

typedef int GameObjectType;

class ExtensibleGameFactory
{
public:
	ExtensibleGameFactory();
	~ExtensibleGameFactory();

	Entity* Create(GameObjectType p_Type);
	void Register(FactoryMaker p_Maker, GameObjectType p_Type);
	void Unregister(GameObjectType p_Type);

private:
	typedef std::map<GameObjectType, FactoryMaker> TypeMap;
	TypeMap m_Makers;
};