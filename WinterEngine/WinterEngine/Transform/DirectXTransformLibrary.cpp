#include "DirectXTransformLibrary.h"

//TODO:: Transform compnoent, not sure where I want the info, but I want it to be XMFLOAT4X4 if we're using windows, which puts me to the mood that we want some sort of interface to it, where
//the graphic and physics(?) engine can work around to get the directx values directly. This because the directX values can compute on the graphics drive in a nice way, and we can upload matrixes to
//graphic card diretly for drawing.

DirectXTransformLibrary::DirectXTransformLibrary()
{

}

DirectXTransformLibrary::~DirectXTransformLibrary()
{

}

void DirectXTransformLibrary::Initialize()
{
	Matrix t_ErrorMatrix;
	t_ErrorMatrix.Direction[0] = 0;
	t_ErrorMatrix.Direction[1] = 0;
	t_ErrorMatrix.Direction[2] = 1;

	t_ErrorMatrix.Position[0] = 0;
	t_ErrorMatrix.Position[1] = 0;
	t_ErrorMatrix.Position[2] = 0;

	t_ErrorMatrix.Up[0] = 0;
	t_ErrorMatrix.Up[1] = 1;
	t_ErrorMatrix.Up[2] = 0;

	m_ErrorMatrixHandle = CreateMatrix(&t_ErrorMatrix);
}

MatrixHandle DirectXTransformLibrary::CreateMatrix(Matrix* p_Matrix)
{
	//make to vectors so we can create matrix using directx
	XMVECTOR t_Eye = XMLoadFloat3(&XMFLOAT3(p_Matrix->Position[0], p_Matrix->Position[1], p_Matrix->Position[2]));
	XMVECTOR t_Direction = XMLoadFloat3(&XMFLOAT3(p_Matrix->Direction[0], p_Matrix->Direction[1], p_Matrix->Direction[2]));
	XMVECTOR t_Up = XMLoadFloat3(&XMFLOAT3(p_Matrix->Up[0], p_Matrix->Up[1], p_Matrix->Up[2]));

	//create matrix
	XMMATRIX t_NewMat = XMMatrixLookToRH(t_Eye, t_Direction, t_Up);

	//store to safe format
	XMFLOAT4X4* t_NewStoreMat = new XMFLOAT4X4();
	XMStoreFloat4x4(t_NewStoreMat, t_NewMat);

	//generate key(handle) and save to library
	std::hash<XMFLOAT4X4*> t_Hasher;
	MatrixHandle o_Handle = t_Hasher(t_NewStoreMat);
	m_TransformMatrixes[o_Handle] = t_NewStoreMat;

	//return handle
	return o_Handle;
}

XMFLOAT4X4* DirectXTransformLibrary::GetMatrix(MatrixHandle p_Handle)
{
	TransformMap::iterator t_TransformMap = m_TransformMatrixes.find(p_Handle);

	//if we got the matrix, return the ID to it
	if (t_TransformMap != m_TransformMatrixes.end())
	{
		return t_TransformMap->second;
	}

	return m_TransformMatrixes[m_ErrorMatrixHandle];
}