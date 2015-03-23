#pragma once
#include "GraphicEngineInterface.h"
#include <vector>
#include <map>
#include <d3d11_2.h>
#include <DirectXMath.h>

using namespace DirectX;

class DirectXGraphicEngine: public GraphicEngineInterface
{
public:
	DirectXGraphicEngine();
	~DirectXGraphicEngine();


private:
	//mesh info chunk that a handle is given of to the game
	struct MeshInfo
	{
		ID3D11Buffer* vertexBuffer;
		ID3D11Buffer* indexBuffer;
	};
	std::map<SGEngine::MeshHandle, MeshInfo> m_MeshKeys;

	//material buffer that a handle is given of to the game
	std::map<SGEngine::MaterialHandle, ID3D11Buffer*> m_MaterialKeys;
};

