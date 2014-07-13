#pragma once
#include <string>

class Resource
{
public:
	Resource();
	~Resource();

	virtual bool Load();
	virtual void Save();
private:
	std::string m_ResourceName;
	
};

