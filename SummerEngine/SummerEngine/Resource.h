#pragma once
#include <string>

class Resource
{
public:
	Resource();
	~Resource();

	virtual bool Load() = 0;
	virtual void Save() = 0;
private:
	std::string m_ResourceName;
	
};

