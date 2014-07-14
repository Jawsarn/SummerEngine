#pragma once

class Serializable
{
public:
	virtual ~Serializable() {};
	virtual bool Read() = 0;
	virtual bool Write() = 0;
	
};

