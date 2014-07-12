#include "FactoryMaker.h"


FactoryMaker::FactoryMaker(Entity* p_Entity)
{
	m_Entity = p_Entity;
}

FactoryMaker::~FactoryMaker()
{
	//maybe delete
}

Entity* FactoryMaker::Create()
{
	return new Entity(*m_Entity);
}