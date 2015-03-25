#pragma once


class TransformLibraryInterface
{
public:
	static TransformLibraryInterface* GetInstance();
	~TransformLibraryInterface();

protected:
	TransformLibraryInterface();

	static TransformLibraryInterface* m_Singleton;
};