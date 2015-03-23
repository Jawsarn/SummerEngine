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

	bool Initialize(HWND p_Handle);

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

	//initialize and handles
	ID3D11Device*			m_Device;
	ID3D11DeviceContext*	m_DeviceContext;
	ID3D11Device1*			m_Device1;
	ID3D11DeviceContext1*	m_DeviceContext1;
	IDXGISwapChain*			m_SwapChain;
	D3D_DRIVER_TYPE			m_DriverType;
	D3D_FEATURE_LEVEL		m_FeatureLevel;

	ID3D11RenderTargetView*		m_RenderTargetView;
	ID3D11UnorderedAccessView*	m_UnorderedAccessView;

	UINT* m_Width;
	UINT* m_Height;

	
	HRESULT InitializeDriverAndVersion(HWND p_HandleWindow);
	HRESULT InitializeRenderTargetView();



	/*
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
	HRESULT CreateRandomVectors();
	HRESULT Renderer::CreateOffsets();

	


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
	ID3D11SamplerState*			m_SamplerStateLinearBorder;
	ID3D11SamplerState*			m_SamplerRandom;

	ID3D11UnorderedAccessView*	m_BackBufferUAV;

	ID3D11ShaderResourceView*	m_GbufferShaderResource[3];
	ID3D11RenderTargetView*		m_GbufferTargetViews[3];

	

	

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
		XMMATRIX ShadowMatrix;
		float Shadow_Width;
		float Shadow_Height;
		XMFLOAT2 Fillers;
	};
	struct SSAOBuffer
	{
		XMFLOAT4 OffsetVectors[14];

		float OcclusionRadius;
		float OcclusionFadeStart;
		float OcclusionFadeEnd;
		float SurfaceEpsilon;
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
	ID3D11Buffer* m_SSAOBuffer;
	ID3D11ShaderResourceView* m_SSAORandomTexture;

	ID3D11UnorderedAccessView* m_SSAOUAV;
	ID3D11ShaderResourceView* m_SSAOSRV;

	ID3D11UnorderedAccessView* m_BlurrUAV;
	ID3D11ShaderResourceView* m_BlurrSRV;

	ID3D11Buffer* m_InstanceBuffer;
	ID3D11ComputeShader* m_DeferredCS;
	ID3D11ComputeShader* m_SSAOCS;
	ID3D11ComputeShader* m_BlurrHorrCS;
	ID3D11ComputeShader* m_BlurrVertCS;

	std::vector<CameraStruct> m_Cameras;

	std::vector<PointLight>		m_PointLights;
	int m_AmountOfPointLights;
	ID3D11Buffer*				m_PointLightsBuffer;
	ID3D11ShaderResourceView*	m_PointLightsBufferSRV;

	ShaderProgram* m_SpriteShaderProgram;
	ShaderProgram* m_FontShaderProgram;
	ShaderProgram* m_DeferredShaderProgram;
	ShaderProgram* m_ShadowMapShaderProgram;
	ShadowMap* m_ShadowMap;
	std::vector<D3D11_VIEWPORT> m_Viewports;

	std::vector<CameraStruct> m_ShadowMapMatrices;
	
	*/
};

