#pragma once
#include "ResourceMaker.h"
#include <string>
#include <map>

class ResourceManager
{
public:
	~ResourceManager();

	void Register(ResourceMaker* p_ResourceMaker);
	Resource* Create(std::string p_ResourceName);



private:
	Resource* LoadResource(std::string p_ResourceName);

	typedef std::map<std::string, ResourceMaker*> MakerMap;
	MakerMap m_Makers;

	typedef std::map<std::string, Resource*> ResourceMap;
	ResourceMap m_Resources;

};

