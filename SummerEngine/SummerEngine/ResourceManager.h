#pragma once
#include "MeshResourceLoadSave.h"
#include <string>
#include <map>

class ResourceManager
{
public:
	

	void Register(ResourceLoadSave* p_ResourceLoadSave);
	Resource* Create(std::string p_ResourceName);
	static ResourceManager* GetInstance();
	
	void SaveResource(Resource* p_Resource);

private:
	Resource* LoadResource(std::string p_ResourceName);
	typedef std::map<std::string, ResourceLoadSave*> MakerMap;
	MakerMap m_Makers;

	typedef std::map<std::string, Resource*> ResourceMap;
	ResourceMap m_Resources;

	ResourceManager();
	~ResourceManager();
	static ResourceManager* m_Singelton;
};

