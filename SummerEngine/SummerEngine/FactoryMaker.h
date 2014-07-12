#pragma once
#include "Entity.h"


class FactoryMaker
{
public:
	FactoryMaker(Entity* p_Entity);
	~FactoryMaker();

	Entity* Create();

private:
	Entity* m_Entity;
};

