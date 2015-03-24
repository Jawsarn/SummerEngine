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

	//initialize directX with shaders, samplers, etc
	bool Initialize(HWND p_Handle, UINT p_Width, UINT p_Height);

	//after initialization, load a engine preset from file
	bool LoadPresetFromFile();

private:
	
	//Grouping of mesh info
	struct MeshInfo
	{
		ID3D11Buffer* vertexBuffer;
		ID3D11Buffer* indexBuffer;
	};

	//Shaderprogram, used to simply group drawmethods, used by functionality as DrawOpaque/Transparent/
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

	//shaderbuffers
	struct PerFrameCBuffer
	{
		XMMATRIX View;
		XMMATRIX Proj;
		XMFLOAT4 EyePosition;
		//XMMATRIX ViewProj;
	};

	struct DeferredComputeCBuffer
	{
		XMFLOAT2 ScreenDimensions;
		XMFLOAT2 CamNearFar;

		XMFLOAT4 AmbientLight;
		XMFLOAT4 ColorOverlay;
	};

	//========================================\\
	///////===========Variables==========\\\\\\\
	/////////=========================\\\\\\\\\\

	//mesh info chunk that a handle is given of to the game
	std::map<SGEngine::MeshHandle, MeshInfo>			m_MeshKeys;

	//material buffer that a handle is given of to the game
	std::map<SGEngine::MaterialHandle, ID3D11Buffer*>	m_MaterialKeys;

	//initialize and handles
	ID3D11Device*				m_Device;
	ID3D11DeviceContext*		m_DeviceContext;
	ID3D11Device1*				m_Device1;
	ID3D11DeviceContext1*		m_DeviceContext1;
	IDXGISwapChain*				m_SwapChain;
	D3D_DRIVER_TYPE				m_DriverType;
	D3D_FEATURE_LEVEL			m_FeatureLevel;

	//Rendertarget resources
	ID3D11RenderTargetView*		m_RenderTargetView;
	ID3D11UnorderedAccessView*	m_UnorderedAccessView;
	ID3D11RenderTargetView*		m_GBufferRTV[3];
	ID3D11ShaderResourceView*	m_GBufferSRV[3];

	//width height resolution
	UINT						m_Width;
	UINT						m_Height;

	//max number of instances, update this dynamically when we ovrrides one size, to beomce 1.5 the size?
	UINT						m_MaxNumOfInstances;
	ID3D11Buffer*				m_InstanceBuffer; //TODO Check if we want to split this into many buffers for each vertex group?


	//rasterizers
	ID3D11RasterizerState*		m_RasterizerNormal;
	ID3D11RasterizerState*		m_RasterizerWireframe;
	
	//depthstencil buffer
	ID3D11Texture2D*			m_DepthStencil;
	ID3D11DepthStencilView*		m_DepthStencilView;

	//depthstencilstates
	ID3D11DepthStencilState*	m_DepthStencilStateOn;
	ID3D11DepthStencilState*	m_DepthStencilStateOff;

	//blendstates
	ID3D11BlendState*			m_BlendStateOn;
	ID3D11BlendState*			m_BlendStateOff;

	//sampelrs
	ID3D11SamplerState*			m_SamplerWrap;
	ID3D11SamplerState*			m_SamplerClamp;
	ID3D11SamplerState*			m_SamplerBorder;
	ID3D11SamplerState*			m_SamplerWrapRandom;

	//shaderprograms
	ShaderProgram*				m_OpaqueShaders;
	ShaderProgram*				m_DeferredComputeShader;

	//constantbuffers
	ID3D11Buffer*				m_PerFrameCBuffer;
	ID3D11Buffer*				m_DeferredComputeCBuffer;



	//========================================\\
	///////===========Functions==========\\\\\\\
	/////////=========================\\\\\\\\\\
	
	//===========INITIALIZATION================\\

	//initialize directx D11.1 is newest we can use
	HRESULT InitializeDriverAndVersion(HWND p_HandleWindow);

	//create the rendertarget/unorderd from backbuffer
	HRESULT InitializeRenderTargetView();

	//creates the sceenviewport sized to the window
	void InitializeViewport();

	//creates normal,wireframe rasterizers
	HRESULT InitializeRasterizers();

	//creates depthbuffer and state for on/off
	HRESULT InitializeDeptpAndStates();

	//creates blendstate for on/off - TODO add more states for different particle systems
	HRESULT InitializeBlendAndStates();

	//creates all the default samplers used for shaders
	HRESULT InitializeSamplers();

	//Compiles shaders from file
	HRESULT InitializeShaders();

	//Creats CBuffers + instance buffer atm TODO::check if we move isntancebuffe
	HRESULT InitializeConstantBuffers();

	//creates GBuffers : (normal/Depth),(diffuse/spec),(notused)
	HRESULT InitializeGBuffers();




	/*
	void SetShaders(ShaderProgram *p_Program);
	void SetTextures(RenderObject* p_Object);
	void SetPerFrameBuffers(std::vector<CameraStruct>* p_Cameras);
	HRESULT CreateRandomVectors();
	HRESULT Renderer::CreateOffsets();

	BOOL m_IsRendering;
	
	
	*/
};

