#pragma once
#include "Stream.h"


/* Abstract class marking the target is used for binary IO*/

class Serializable
{
public:
	virtual ~Serializable() {};

	//needs to have a implementation how to read and write the object
	virtual bool Read(Stream &p_Stream) = 0;
	virtual bool Write(Stream &p_Stream) = 0;

	//used to fix adress translations
	virtual void Fixup() = 0;

};

