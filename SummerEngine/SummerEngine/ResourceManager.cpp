#include "ResourceManager.h"
#include <assert.h>

ResourceManager* ResourceManager::m_Singelton = nullptr;
ResourceManager* ResourceManager::GetInstance()
{
	if (m_Singelton == nullptr)
	{
		m_Singelton = new ResourceManager();
	}
	return m_Singelton;
}

ResourceManager::ResourceManager()
{
}

ResourceManager::~ResourceManager()
{
}

void ResourceManager::Register(ResourceLoadSave* p_ResourceLoadSave)
{
	assert(p_ResourceLoadSave != nullptr);

	m_Makers[std::string(p_ResourceLoadSave->GetExtension())] = p_ResourceLoadSave;
}

Resource* ResourceManager::Create(const std::string p_ResourceName)
{
	ResourceMap::iterator t_ResMapIt = m_Resources.find(p_ResourceName);

	if (t_ResMapIt != m_Resources.end())
	{
		return t_ResMapIt->second;
	}

	Resource* o_Resource = LoadResource(p_ResourceName);
	if (o_Resource == nullptr)
	{
		return o_Resource;
	}

	m_Resources[p_ResourceName] = o_Resource;
	return o_Resource;
}

Resource* ResourceManager::LoadResource(std::string p_ResourceName)
{
	std::size_t t_Spot = p_ResourceName.find_last_of(".");
	if (t_Spot == std::string::npos)
	{
		 //no . found, that'd be an error filename
		return nullptr;
	}
	std::size_t t_Length = p_ResourceName.length();

	std::string t_Extension = p_ResourceName.substr(t_Spot,t_Length);
	
	MakerMap::iterator t_It = m_Makers.find(t_Extension);
	if (t_It == m_Makers.end())
	{
		return nullptr;
	}

	return t_It->second->Load(p_ResourceName);
}

void ResourceManager::SaveResource(Resource* p_Resource)
{
	std::size_t t_Spot = p_Resource->GetName().find_last_of(".");
	if (t_Spot == std::string::npos)
	{
		//no . found, that'd be an error filename
		return;
	}
	std::size_t t_Length = p_Resource->GetName().length();

	std::string t_Extension = p_Resource->GetName().substr(t_Spot, t_Length);

	MakerMap::iterator t_It = m_Makers.find(t_Extension);
	if (t_It == m_Makers.end())
	{
		return;
	}

	t_It->second->Save(p_Resource);
	m_Resources[p_Resource->GetName()] = p_Resource;
}
