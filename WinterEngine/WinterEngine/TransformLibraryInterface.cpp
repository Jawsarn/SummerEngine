#include "TransformLibraryInterface.h"
#include "DirectXTransformLibrary.h"

TransformLibraryInterface* TransformLibraryInterface::m_Singleton = nullptr;

TransformLibraryInterface* TransformLibraryInterface::GetInstance()
{
	if (m_Singleton == nullptr)
	{
		m_Singleton = new DirectXTransformLibrary();
	}
	return m_Singleton;
}

TransformLibraryInterface::TransformLibraryInterface()
{

}

TransformLibraryInterface::~TransformLibraryInterface()
{

}