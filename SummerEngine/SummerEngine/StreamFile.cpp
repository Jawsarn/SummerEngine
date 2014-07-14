#include "StreamFile.h"


StreamFile::StreamFile()
{
	m_File = nullptr;
	m_ReadMode = false;
	m_WriteMode = false;
}


StreamFile::~StreamFile()
{
}

bool StreamFile::OpenFileRead(std::string p_FileName)
{
	if (m_File != nullptr) //if file already open close
	{
		return false;
	}
	fopen_s(&m_File, p_FileName.c_str(), "r");
	
	m_ReadMode = (m_File != nullptr);

	return m_ReadMode;
}

bool StreamFile::OpenFileWrite(std::string p_FileName)
{
	if (m_File != nullptr) //if file already open close
	{
		return false;
	}
	fopen_s(&m_File, p_FileName.c_str(), "wb");

	m_WriteMode = (m_File != nullptr);

	return m_WriteMode;
}

void StreamFile::Close()
{
	if (m_File != nullptr) //if file already open close
	{
		fclose(m_File);
	}
	m_WriteMode = false;
	m_ReadMode = false;
}

int StreamFile::Read(int p_BytesToRead, void* p_Buffer)
{
	assert(p_Buffer != nullptr); //if pointer at nullptr no memory space to save it have been asked for

	if (!m_ReadMode)
	{
		return 0;
	}

	return fread(p_Buffer, 1, p_BytesToRead, m_File);
}

int StreamFile::Write(int p_BytesToWrite, const void* p_Buffer)
{
	assert(p_Buffer != nullptr);

	if (!m_WriteMode)
	{
		return 0;
	}

	return fwrite(p_Buffer,1 ,p_BytesToWrite,m_File);
}

bool StreamFile::SetCurPos(int p_Pos)
{
	if (!m_WriteMode && !m_ReadMode)
	{
		return false;
	}

	return (fseek(m_File, p_Pos, SEEK_SET) == 0);
}

int StreamFile::GetCurPos()
{
	if (!m_WriteMode && !m_ReadMode)
	{
		return false;
	}

	return ftell(m_File);
}