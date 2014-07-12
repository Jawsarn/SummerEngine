#pragma once
#include "Entity.h"
#include <list>

#include "TransformComponent.h"
class Scene
{
public:
	Scene();
	~Scene();
	
private:
	std::list<Entity*> m_EntiyParents;
	//Click on parent to show entity children
};

