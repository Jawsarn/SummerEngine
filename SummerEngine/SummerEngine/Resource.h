#pragma once
//#include "ResourceManager.h"
#include <string>

/*virtual type to mark the object as an Resource, Load and Save should be in the LoadSaver of Resource type*/

class ResourceManager;

class Resource
{
public:
	virtual ~Resource() {};
	typedef std::string ResourceType;

	virtual void SetName(std::string p_Name) = 0;
	virtual const std::string GetName() = 0;
	virtual const ResourceType GetType() const = 0;


	//virtual bool Load() = 0;
	//virtual void Save() = 0;
protected:
	std::string m_FileName;

};
