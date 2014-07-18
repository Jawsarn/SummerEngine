#pragma once
//#include "ResourceManager.h"
#include <string>

class ResourceManager;

class Resource
{
public:
	virtual ~Resource() {};
	typedef std::string ResourceType;

	virtual const std::string &GetName() const = 0;
	virtual const ResourceType GetType() const = 0;


	//virtual bool Load() = 0;
	//virtual void Save() = 0;
protected:
	std::string m_FileName;

};
