#pragma once
#include <string>

class Stream
{
public:
	Stream();
	~Stream();
	virtual int Read() = 0;
	virtual int Write() = 0;

	virtual bool SetCurPos() = 0;
	virtual int GetCurPos() = 0;

protected:
	int ReadInt();
	float ReadFloat();
	std::string ReadString();

	bool WriteInt();
	bool WriteFloat();
	bool WriteString();
};

