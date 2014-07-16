#pragma once
#include "MeshResourceLoadSave.h"
#include <string>
#include <map>

class ResourceManager
{
public:
	~ResourceManager();

	void Register(ResourceLoadSave* p_ResourceLoadSave);
	Resource* Create(std::string p_ResourceName);



private:
	Resource* LoadResource(std::string p_ResourceName);

	typedef std::map<std::string, ResourceLoadSave*> MakerMap;
	MakerMap m_Makers;

	typedef std::map<std::string, Resource*> ResourceMap;
	ResourceMap m_Resources;

};

