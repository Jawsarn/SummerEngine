#pragma once
#include <d3d11_1.h>
#include <DirectXMath.h>
#include "Mesh.h"
#include "Component.h"
#include "ShadowMap.h"
#include "ScreenManager.h"
#include "Font.h"

using namespace DirectX;

//#define _DEBUG

#define MAX_INSTANCEBUFFER_SIZE 1000
#define THREAD_BLOCK_DIMENSIONS 16
#define MAX_NUM_OF_LIGHTS 1024

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
		XMFLOAT3 Position;
		//XMFLOAT4X4 ViewProj;
	};

	typedef std::vector<RenderObject*> RenderObjects;


	static Renderer* GetInstance();
	bool Renderer::Initialize(UINT p_Width, UINT p_Height, HWND p_HandleWindow);

	void CreateBuffer(D3D11_BUFFER_DESC* p_Desc, D3D11_SUBRESOURCE_DATA* p_Data, ID3D11Buffer** o_Buffer);
	bool CreateTexture(const wchar_t * p_FileName, ID3D11ShaderResourceView** t_NewSRV);

	void SetViewports(std::vector<D3D11_VIEWPORT> p_Viewports);
	void SetCameras(std::vector<CameraStruct> p_Cameras);
	void BeginRender();
	void RenderOpaque(RenderObjects* p_RenderObjects);
	void RenderShadowmaps(RenderObjects* p_RenderObjects);
	void RenderSprites();
	void ComputeDeferred();
	void RenderTransparent(RenderObjects* p_RenderObjects);
	void EndRender();

private:
	Renderer();
	~Renderer();

	struct ShaderProgram
	{
		ID3D11InputLayout* InputLayout;
		ID3D11VertexShader* VertexShader;
		ID3D11GeometryShader* GeometryShader;
		ID3D11HullShader* HullShader;
		ID3D11DomainShader* DomainShader;
		ID3D11PixelShader* PixelShader;
		ID3D11ComputeShader* ComputeShader;
		ShaderProgram()
		{
			InputLayout = nullptr;
			VertexShader = nullptr;
			GeometryShader = nullptr;
			HullShader = nullptr;
			DomainShader = nullptr;
			PixelShader = nullptr;
			ComputeShader = nullptr;
		}
	};

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

	void SetShaders(ShaderProgram *p_Program);
	void SetTextures(RenderObject* p_Object);
	void SetPerFrameBuffers(std::vector<CameraStruct>* p_Cameras);

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
	ID3D11RasterizerState*		m_RasterizerStateShadowMap;
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
		XMFLOAT4 EyePosition;
		//XMMATRIX ViewProj;
	};
	
	struct PerComputeBuffer
	{
		XMFLOAT2 ScreenDimensions;
		XMFLOAT2 CamNearFar;

		XMFLOAT4 AmbientLight;
		XMFLOAT4 ColorOverlay;
	};

	struct ShadowMapBuffer
	{
		XMMATRIX ViewInvers;
		XMMATRIX WorldViewProj;
		float Shadow_Width;
		float Shadow_Height;
		XMFLOAT2 Fillers;
	};

	struct PointLight
	{
		
		XMFLOAT3 Position;
		float Radius;

		XMFLOAT3 Color;
		float Filler;
		PointLight()
		{
			Position = XMFLOAT3(0,0,0);
			Radius = 0;
			Color = XMFLOAT3(0, 0, 0);
			Filler = 0;
		}
		PointLight(XMFLOAT3 p_Pos, float p_rad, XMFLOAT3 p_Col)
		{
			Position = p_Pos;
			Radius = p_rad;
			Color = p_Col;
			Filler = 0;
		}
	};

	
	ID3D11Buffer* m_TestPerFrameBuffer;
	ID3D11Buffer* m_PerComputeBuffer;
	ID3D11Buffer* m_ShadowMapBuffer;

	ID3D11Buffer* m_InstanceBuffer;
	ID3D11ComputeShader* m_DeferredCS;


	std::vector<CameraStruct> m_Cameras;

	std::vector<PointLight>		m_PointLights;
	int m_AmountOfPointLights;
	ID3D11Buffer*				m_PointLightsBuffer;
	ID3D11ShaderResourceView*	m_PointLightsBufferSRV;

	ShaderProgram* m_SpriteShaderProgram;
	ShaderProgram* m_DeferredShaderProgram;
	ShaderProgram* m_ShadowMapShaderProgram;
	ShadowMap* m_ShadowMap;
	std::vector<D3D11_VIEWPORT> m_Viewports;

	std::vector<CameraStruct> m_ShadowMapMatrices;

	Font* m_Font;	//	test
};

