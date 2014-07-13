#pragma once
#include "Resource.h"
#include <string>
#include <map>

class ResourceManager
{
public:
	ResourceManager();
	~ResourceManager();

	Resource* CreateTexture();
	Resource* CreateAnimation();
	Resource* CreateMesh();

private:
	std::map<std::string, Resource*> m_Resources;
};

