#pragma once
#include "MatrixLibraryInterface.h"
#include "../Graphics/DirectXGraphicEngine.h"
#include <DirectXMath.h>
#include <map>

//TODO:: Transform compnoent, not sure where I want the info, but I want it to be XMFLOAT4X4 if we're using windows, which puts me to the mood that we want some sort of interface to it, where
//the graphic and physics(?) engine can work around to get the directx values directly. This because the directX values can compute on the graphics drive in a nice way, and we can upload matrixes to
//graphic card diretly for drawing.
using namespace DirectX;

class DirectXMatrixLibrary : public MatrixLibraryInterface
{
public:
	DirectXMatrixLibrary();
	~DirectXMatrixLibrary();
	void Initialize();

	//create functions
	MatrixHandle CreateMatrix(Matrix* p_Matrix);
	MatrixHandle CreateMatrix(FoVProjMatrix* p_Matrix);
	MatrixHandle CreateMatrix(OrthoProjMatrix* p_Matrix);

	//get functions
	XMFLOAT4X4* GetMatrix(MatrixHandle p_Handle);

private:
	
	typedef std::map<MatrixHandle, DirectX::XMFLOAT4X4*> TransformMap;
	TransformMap m_TransformMatrixes;
	UINT m_ErrorMatrixHandle;

	//functions
	MatrixHandle DirectXMatrixLibrary::StoreMatrix(CXMMATRIX& p_NewMat);
};