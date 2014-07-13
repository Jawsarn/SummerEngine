#pragma once
#include <d3d11_1.h>
#include <DirectXMath.h>

using namespace DirectX;

//#define _DEBUG

class Renderer
{
public:
	static Renderer* GetInstance();
	bool Renderer::Initialize(UINT p_Width, UINT p_Height, HWND p_HandleWindow);

private:
	Renderer();
	~Renderer();

	HRESULT InitializeDriverAndVersion(HWND p_HandleWindow);
	HRESULT InitializeRenderTargetView();
	void InitializeViewports();
	HRESULT InitializeRasterizers();
	HRESULT InitializeDeptpAndStates();
	HRESULT InitializeBlendAndStates();
	HRESULT Renderer::InitializeShaders();

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
	ID3D11SamplerState*			m_SamplerStateLinearWrap;

	ID3D11UnorderedAccessView*	m_BackBufferUAV;

	ID3D11ShaderResourceView*	m_GbufferShaderResource[3];
	ID3D11RenderTargetView*		m_GbufferTargetViews[3];

	

	UINT* m_Width;
	UINT* m_Height;

	static Renderer* m_Singleton;
};

