#pragma once
#include "TransformLibraryInterface.h"
#include <DirectXMath.h>
#include <map>



class DirectXTransformLibrary : public TransformLibraryInterface
{
public:
	DirectXTransformLibrary();
	~DirectXTransformLibrary();



private:
	std::map<DirectX::XMFLOAT4X4, unsigned int> m_TransformMatrixes;

};