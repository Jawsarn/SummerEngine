#pragma once
#include "FactoryMaker.h"

template <class Factory>

class Registrar
{
public:
	Registrar(Factory& factory)
	{
		factory.Register(new FactoryMaker<Type>);
	}
};
