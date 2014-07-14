#pragma once

class Serializable
{
public:
	virtual ~Serializable() {};
	virtual bool Write() = 0;
	virtual bool Read() = 0;
};

