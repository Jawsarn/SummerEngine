#pragma once
#include "Stream.h"

class Serializable
{
public:
	virtual ~Serializable() {};
	virtual bool Read(Stream &p_Stream) = 0;
	virtual bool Write(Stream &p_Stream) = 0;
	
};

