#pragma once
#include <string>

class Stream
{
public:
	virtual ~Stream() {};
	virtual int Read(int p_BytesToRead, void* p_Buffer) = 0;
	virtual int Write(int p_BytesToWrite, const void* p_Buffer) = 0;

	virtual bool SetCurPos(int p_Pos) = 0;
	virtual int GetCurPos() = 0;

	
};

int ReadInt(Stream &p_Stream);


float ReadFloat(Stream &p_Stream);


bool ReadBool(Stream &p_Stream);


std::string ReadString(Stream &p_Stream);


bool WriteInt(Stream &p_Stream, int p_Val);


bool WriteFloat(Stream &p_Stream, float p_Val);


bool WriteBool(Stream &p_Stream, bool p_Val);


bool WriteString(Stream &p_Stream, const std::string &p_Val);
