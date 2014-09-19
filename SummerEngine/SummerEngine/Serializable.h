#pragma once
#include "Stream.h"

/* Abstract class marking the target is used for binary IO*/

class Serializable
{
public:
	virtual ~Serializable() {};
	virtual bool Read(Stream &p_Stream) = 0;
	virtual bool Write(Stream &p_Stream) = 0;
	virtual void Fixup() = 0;
	
};

