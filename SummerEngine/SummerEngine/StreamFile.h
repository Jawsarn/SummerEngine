#pragma once
#include "Stream.h"
#include <assert.h>

/*Class used to stream data to a file can read and write all basic types and string*/

class StreamFile: public Stream
{
public:
	StreamFile();
	virtual ~StreamFile();

	bool OpenFileRead(std::string p_FileName);
	bool OpenFileWrite(std::string p_FileName);
	void Close();

	virtual int Read(int p_BytesToRead, void* p_Buffer);
	virtual int Write(int p_BytesToWrite, const void* p_Buffer);

	virtual bool SetCurPos(int p_Pos);
	virtual int GetCurPos();
private:
	FILE* m_File;
	bool m_ReadMode;
	bool m_WriteMode;
};

