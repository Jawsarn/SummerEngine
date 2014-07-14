#pragma once
#include "Stream.h"


class StreamFile:Stream
{
public:
	StreamFile();
	~StreamFile();

	virtual int Read();
	virtual int Write();

	virtual bool SetCurPos();
	virtual int GetCurPos();
};

