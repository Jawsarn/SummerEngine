#include "ExtensibleGameFactory.h"


ExtensibleGameFactory::ExtensibleGameFactory()
{
}


ExtensibleGameFactory::~ExtensibleGameFactory()
{
}

Entity* ExtensibleGameFactory::Create(GameObjectType p_Type)
{
	TypeMap::iterator it = m_Makers.find(p_Type);
	if (it == m_Makers.end())
	{
		return nullptr;
	}
	FactoryMaker* t_Maker = (*it).second;
	return t_Maker->Create();
}

void Register(FactoryMaker p_Maker, GameObjectType p_Type)
{

}

void Unregister(GameObjectType p_Type)
{

}