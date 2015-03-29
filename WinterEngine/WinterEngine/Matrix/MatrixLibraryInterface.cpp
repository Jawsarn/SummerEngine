#include "MatrixLibraryInterface.h"
#include "DirectXMatrixLibrary.h"

//TODO:: Transform compnoent, not sure where I want the info, but I want it to be XMFLOAT4X4 if we're using windows, which puts me to the mood that we want some sort of interface to it, where
//the graphic and physics(?) engine can work around to get the directx values directly. This because the directX values can compute on the graphics drive in a nice way, and we can upload matrixes to
//graphic card diretly for drawing.

MatrixLibraryInterface* MatrixLibraryInterface::m_Singleton = nullptr;

MatrixLibraryInterface* MatrixLibraryInterface::GetInstance()
{
	if (m_Singleton == nullptr)
	{
		m_Singleton = new DirectXMatrixLibrary();
	}
	return m_Singleton;
}

MatrixLibraryInterface::MatrixLibraryInterface()
{

}

MatrixLibraryInterface::~MatrixLibraryInterface()
{

}