#pragma once
#include <string>

namespace IO
{
	/*IO class, can be used for files or maybe network in future*/
	//TODO::Streams should be version dependent, and have translations between version, add this when we're getting to a point where context is vital
	class Stream
	{
	public:
		virtual ~Stream() {};

		//all streamtypes needs to be able to read and wirte
		virtual int Read(int p_BytesToRead, void* p_Buffer) = 0;
		virtual int Write(int p_BytesToWrite, const void* p_Buffer) = 0;

		virtual bool SetCurPos(int p_Pos) = 0;
		virtual int GetCurPos() = 0;


	};


	//types that are normally used, could add a Write buffer as well her...
	int ReadInt(Stream &p_Stream);

	unsigned int ReadUnsigned(Stream &p_Stream);

	float ReadFloat(Stream &p_Stream);

	bool ReadBool(Stream &p_Stream);

	std::string ReadString(Stream &p_Stream);

	bool WriteInt(Stream &p_Stream, int p_Val);

	bool WriteUnsigned(Stream &p_Stream, unsigned int p_Val);

	bool WriteFloat(Stream &p_Stream, float p_Val);

	bool WriteBool(Stream &p_Stream, bool p_Val);

	bool WriteString(Stream &p_Stream, const std::string &p_Val);

}