#pragma once
#include "Stream.h"
#include <assert.h>

/*Class used to stream data to a file can read and write all basic types and string*/
namespace IO
{

	class StreamFile : public Stream
	{
	public:
		StreamFile();
		virtual ~StreamFile();

		//open and close the file
		bool OpenFileRead(std::string p_FileName);
		bool OpenFileWrite(std::string p_FileName);
		void Close();

		//implementation of read and write to file
		virtual int Read(int p_BytesToRead, void* p_Buffer);
		virtual int Write(int p_BytesToWrite, const void* p_Buffer);

		//if we want to find something in the files(example: finding an orc entity in a file of all entities)
		virtual bool SetCurPos(int p_Pos);

		//get where we are.. not sure if we need this one mby?
		virtual int GetCurPos();

	private:
		//our file
		FILE* m_File;

		//if we're reading or writing, error checking!
		bool m_ReadMode;
		bool m_WriteMode;
	};

}
