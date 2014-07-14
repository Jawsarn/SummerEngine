#pragma once
#include <string>

class Stream
{
public:
	virtual ~Stream() {};
	virtual int Read() = 0;
	virtual int Write() = 0;

	virtual bool SetCurPos() = 0;
	virtual int GetCurPos() = 0;

	
};

int ReadInt()
{
	return 0;
}

float ReadFloat()
{
	return 0.0f;
}

bool ReadBool()
{
	return true;
}

std::string ReadString()
{
	return "";
}

bool WriteInt()
{
	return true;
}

bool WriteFloat()
{
	return true;
}

bool WriteBool()
{
	return true;
}

bool WriteString()
{
	return true;
}
