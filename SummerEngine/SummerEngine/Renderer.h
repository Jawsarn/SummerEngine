#pragma once
#include <d3d11_1.h>
#include <DirectXMath.h>
#include "Mesh.h"
#include "Component.h"
#include "Rectangles.h"//testar

using namespace DirectX;

//#define _DEBUG

#define MAX_INSTANCEBUFFER_SIZE 1000

class Renderer
{
public:
	struct RenderObject
	{
		int BufferNum;
		Component* m_Component;
	};
	struct CameraStruct
	{
		XMFLOAT4X4 View;
		XMFLOAT4X4 Proj;
		XMFLOAT4X4 ViewProj;
	};
	typedef std::vector<RenderObject*> RenderObjects;


	static Renderer* GetInstance();
	bool Renderer::Initialize(UINT p_Width, UINT p_Height, HWND p_HandleWindow);

	void CreateBuffer(D3D11_BUFFER_DESC* p_Desc, D3D11_SUBRESOURCE_DATA* p_Data, ID3D11Buffer** o_Buffer);

	void SetViewports(std::vector<D3D11_VIEWPORT> p_Viewports);
	void SetCameras(std::vector<CameraStruct> p_Cameras);
	void BeginRender();
	void RenderOpaque(RenderObjects* p_RenderObjects);
	void ComputeDeferred();
	void RenderTransparent(RenderObjects* p_RenderObjects);
	void EndRender();


private:
	Renderer();
	~Renderer();

	HRESULT InitializeDriverAndVersion(HWND p_HandleWindow);
	HRESULT InitializeRenderTargetView();
	//void InitializeViewports();
	HRESULT InitializeRasterizers();
	HRESULT InitializeDeptpAndStates();
	HRESULT InitializeBlendAndStates();
	HRESULT InitializeShaders();
	HRESULT InitializeConstantBuffers();
	HRESULT InitializeGBuffers();
	HRESULT InitializeSamplerState();
	


	//initialize and handles
	ID3D11Device*			m_Device;
	ID3D11DeviceContext*	m_DeviceContext;
	ID3D11Device1*			m_Device1;
	ID3D11DeviceContext1*	m_DeviceContext1;
	IDXGISwapChain*			m_SwapChain;
	D3D_DRIVER_TYPE			m_DriverType;
	D3D_FEATURE_LEVEL		m_FeatureLevel;


	//basic rendering stuff
	ID3D11RenderTargetView*		m_RenderTargetView;
	ID3D11Texture2D*			m_DepthStencil;
	ID3D11DepthStencilView*		m_DepthStencilView;
	ID3D11RasterizerState*		m_RasterizerStateNormal;
	ID3D11RasterizerState*		m_RasterizerStateWireframe;
	ID3D11BlendState*			m_BlendStateOn;
	ID3D11BlendState*			m_BlendStateOff;
	ID3D11DepthStencilState*	m_DepthStateOn;
	ID3D11DepthStencilState*	m_DepthStateOff;
	ID3D11DepthStencilState*	m_DepthStateNoWrite;
	ID3D11DepthStencilState*	m_LessEqualDepthState;
	ID3D11SamplerState*			m_SamplerStateWrap;
	ID3D11SamplerState*			m_SamplerStateLinearClamp;

	ID3D11UnorderedAccessView*	m_BackBufferUAV;

	ID3D11ShaderResourceView*	m_GbufferShaderResource[3];
	ID3D11RenderTargetView*		m_GbufferTargetViews[3];

	

	UINT* m_Width;
	UINT* m_Height;

	static Renderer* m_Singleton;
	BOOL m_IsRendering;

	//test thigns
	struct PerFrameTestBuffer
	{
		XMMATRIX View;
		XMMATRIX Proj;
		XMMATRIX ViewProj;
	};

	ID3D11Buffer* m_TestPerFrameBuffer;

	ID3D11Buffer* m_InstanceBuffer;
	ID3D11PixelShader* m_TestPixelShader;
	ID3D11VertexShader* m_TestVertexShader;
	ID3D11InputLayout* m_TestLayout;
	void Renderer::SetShaders();
	std::vector<CameraStruct> m_Cameras;


	Rectangles rect;//testar
	
};

