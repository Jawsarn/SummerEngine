#pragma once
#include "Resource.h"
#include <string>
#include <map>

class ResourceManager
{
public:
	ResourceManager();
	~ResourceManager();

	Resource* CreateTexture(std::string p_ResourceName);
	Resource* CreateAnimation(std::string p_ResourceName);
	Resource* CreateMesh(std::string p_ResourceName);

private:
	std::map<std::string, Resource*> m_Resources;
};

