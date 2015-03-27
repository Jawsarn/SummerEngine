#include "Stream.h"
#include <Windows.h>

namespace IO
{

	//types that are normally used, could add a Write buffer as well her...

	int ReadInt(Stream &p_Stream)
	{
		int o_Val = 0;
		p_Stream.Read(sizeof(int), &o_Val);
		return o_Val;
	}

	unsigned int ReadUnsigned(Stream &p_Stream)
	{
		unsigned int o_Val = 0;
		p_Stream.Read(sizeof(unsigned int), &o_Val);
		return o_Val;
	}

	float ReadFloat(Stream &p_Stream)
	{
		float o_Val = 0.0f;
		p_Stream.Read(sizeof(float), &o_Val);
		return o_Val;
	}

	bool ReadBool(Stream &p_Stream)
	{
		bool o_Val = false;
		p_Stream.Read(sizeof(bool), &o_Val);
		return o_Val;
	}

	std::string ReadString(Stream &p_Stream)
	{
		int t_StringLenght = ReadInt(p_Stream);
		char o_Text[512];
		p_Stream.Read(t_StringLenght, o_Text);

		return std::string(o_Text);
	}

	bool WriteInt(Stream &p_Stream, int p_Val)
	{
		int t_NumbersWritten = p_Stream.Write(sizeof(int), &p_Val);
		return (sizeof(int) == t_NumbersWritten);
	}

	bool WriteUnsigned(Stream &p_Stream, unsigned int p_Val)
	{
		int t_NumbersWritten = p_Stream.Write(sizeof(unsigned int), &p_Val);
		return (sizeof(unsigned int) == t_NumbersWritten);
	}

	bool WriteFloat(Stream &p_Stream, float p_Val)
	{
		int t_NumbersWritten = p_Stream.Write(sizeof(float), &p_Val);
		return (sizeof(float) == t_NumbersWritten);
	}

	bool WriteBool(Stream &p_Stream, bool p_Val)
	{
		int t_NumbersWritten = p_Stream.Write(sizeof(bool), &p_Val);
		return (sizeof(bool) == t_NumbersWritten);
	}

	bool WriteString(Stream &p_Stream, const std::string &p_Val)
	{
		int t_StringLenght = p_Val.length() + 1;
		if (!WriteInt(p_Stream, t_StringLenght))
		{
			return false;
		}

		return (p_Stream.Write(t_StringLenght, p_Val.c_str()) == t_StringLenght);
	}


}