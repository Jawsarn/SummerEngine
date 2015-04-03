 #pragma once
#include "GraphicEngineInterface.h"
#include <vector>
#include <map>
#include <d3d11_2.h>
#include <DirectXMath.h>
#include <string>

//TODO::change all hashes to not be returning UINT but the t_size instead, for 32-64 bit compability
using namespace DirectX;

class DirectXGraphicEngine: public GraphicEngineInterface
{
public:
	DirectXGraphicEngine();
	~DirectXGraphicEngine();

	void Release();

	//initialize directX with shaders, samplers, etc
	bool Initialize(HWND p_Handle, UINT p_Width, UINT p_Height);

	//after initialization, load a engine preset from file
	bool LoadPresetFromFile();

	//========================================\\
	///////Create/Load Resource Functions\\\\\\\
	/////////=========================\\\\\\\\\\
		
	//Creates a handle to a mesh resource in the engine
	MeshHandle CreateModel( const std::string& p_Name, std::vector<VertexPosNormalTangentTex>* p_Vertices, std::vector<Index>* p_Indicies );

	//Creates a handle to a material resource in the engine
	MaterialHandle CreateMaterial( const std::string& p_Name, Material* p_Mat);

	//Loads a mesh resource from file into the engine and returns a handle to it TODO::set full virtual
	bool LoadModel( const std::string& p_Name, MeshHandle* o_MeshHandle );

	//Loads a material resource from file into the engine and returns a handle to it TODO::set full virtual
	MaterialHandle LoadMaterial(const std::string& p_Name);

	//========================================\\
	///////=========Draw Functions=======\\\\\\\
	/////////=========================\\\\\\\\\\

	//Needs to be called befor all other drawcalls, and ended with "EndDraw()"
	void BeginDraw();

	//Call "BeginDraw()" befor, draws nontransparent, call "ComputeDeferred()" after
	void DrawOpaque(std::vector<RenderObject*>* p_RenderObects);

	//Computes deferrred rendering, call befor "DrawTransparent"
	void ComputeDeferred();

	//Call after "ComputerDeferred()", draws transparent objects
	void DrawTransparent(std::vector<RenderObject*>* p_RenderObects);

	//Call when done drawing, needs to be started with "BeginDraw()"
	void EndDraw();

	//========================================\\
	///////=======Utility Functions======\\\\\\\
	/////////=========================\\\\\\\\\\

	void UseCamera(SGEngine::Camera p_Camera, UINT p_Slot);

private:
	
	//Grouping of mesh info
	struct MeshInfo
	{
		ID3D11Buffer* vertexBuffer;
		ID3D11Buffer* indexBuffer;
	};

	//Materials are saved on the engine, and a key is given to the components using them
	struct MaterialInfo
	{
		struct MaterialValues
		{
			float Ns;					//Shininess of the material
			XMFLOAT3 Ka;				//Ambient color (r,g,b)

			float Ni;					//Reflection index
			XMFLOAT3 Kd;				//Diffuse color (r,g,b)

			float D;					//Transparency Tr (alpha)
			XMFLOAT3 Ks;				//Specular color (r,g,b)

			XMFLOAT3 Tf;				//Color Transperancy color (d or Tr)
			float Ke;					//Emissive color

			UINT Illum;					//Define the illumination model: illum = 1 a flat material with no specular highlights, illum = 2 denotes the presence of specular highlights
			XMUINT3 Fillers;
		};

		//buffer to material
		ID3D11Buffer* m_MatBuffer;

		//group to be able to send to buffer easy
		MaterialValues m_MatValues;

		

		UINT m_Map_Kd;		//diffuse
		UINT m_Map_Ka;		//ambient
		UINT m_Map_Ks;		//specular
		UINT m_Map_Ke;		//emissive fucked up shit
		UINT m_Map_Ns;		//specular shinyness
		UINT m_Map_D;		//transparency
		UINT m_Bump;			//normal map
		UINT m_Disp;			//displacment map
		UINT m_Occulsion;	//diffuse blackmap

		//default constructor
		MaterialInfo()
		{
			m_MatValues.Ns = m_MatValues.Ni = m_MatValues.D = m_MatValues.Ke = 0.0f;
			m_MatValues.Ka = m_MatValues.Kd = m_MatValues.Ks = m_MatValues.Tf = XMFLOAT3(0, 0, 0);
			m_MatValues.Fillers = XMUINT3(0, 0, 0);
			m_MatValues.Illum = m_Map_Kd = m_Map_Ka = m_Map_Ks = m_Map_Ke = m_Map_Ns = m_Map_D = m_Bump = m_Disp = m_Occulsion = 0;
		}
		//copyconstructor from the interface material, to easy swap over info
		MaterialInfo(SGEngine::Material& p_Material)
		{
			m_MatValues.Ns = p_Material.Ns;
			m_MatValues.Ka = XMFLOAT3(p_Material.Ka[0], p_Material.Ka[1], p_Material.Ka[2]);

			m_MatValues.Ni = p_Material.Ni;
			m_MatValues.Kd = XMFLOAT3(p_Material.Kd[0], p_Material.Kd[1], p_Material.Kd[2]);

			m_MatValues.D = p_Material.D;
			m_MatValues.Ks = XMFLOAT3(p_Material.Ks[0], p_Material.Ks[1], p_Material.Ks[2]);

			m_MatValues.Tf = XMFLOAT3(p_Material.Tf[0], p_Material.Tf[1], p_Material.Tf[2]);
			m_MatValues.Ke = p_Material.Ke;

			m_MatValues.Illum = p_Material.Illum;
			m_MatValues.Fillers = XMUINT3(0, 0, 0);

			m_Map_Kd = m_Map_Ka = m_Map_Ks = m_Map_Ke = m_Map_Ns = m_Map_D = m_Bump = m_Disp = m_Occulsion = 0;
		}

	};

	struct View
	{
		D3D11_VIEWPORT viewport;
		SGEngine::Camera camera;
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

		void Release()
		{
			if( InputLayout	  )	InputLayout->Release();
			if( VertexShader  )	VertexShader->Release();
			if( GeometryShader) GeometryShader->Release();
			if( HullShader	  )	HullShader->Release();
			if( DomainShader  )	DomainShader->Release();
			if( PixelShader	  )	PixelShader->Release();
			if( ComputeShader ) ComputeShader->Release();
		}
	};

	//shaderbuffers
	struct PerFrameCBuffer
	{
		XMFLOAT4X4 View;
		XMFLOAT4X4 Proj;
		XMFLOAT4X4 ViewProj;
		XMFLOAT4 EyePosition;
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

	//hashfunctionsfor keys
	std::hash<MaterialInfo*>	t_MaterialHash;
	std::hash<MeshInfo*>		t_MeshHash;

	//Maps from Handles to strings
	typedef std::map<std::string, UINT> MeshIDMap;
	typedef std::map<std::string, UINT> MaterialIDMap;
	typedef std::map<std::string, UINT> TextureIDMap;

	//
	typedef std::map<SGEngine::MeshHandle,		MeshInfo*>					MeshMap;
	typedef std::map<SGEngine::MaterialHandle,	MaterialInfo*>				MaterialMap;
	typedef std::map<SGEngine::TextureHandle,	ID3D11ShaderResourceView* > TextureMap;

	//maps from string -> ID
	MeshIDMap					m_MeshIDMap;
	MaterialIDMap				m_MaterialIDMap;
	TextureIDMap				m_TextureIDMap;

	//maps from ID -> resource
	MeshMap						m_MeshKeys;
	MaterialMap					m_MaterialKeys;
	TextureMap					m_TextureMap;

	//functions checking, if we've begon drawing or not
	BOOL						m_IsDrawing;
	UINT						m_VsyncCode;

	//error tools
	UINT						m_ErrorTextureID;
	UINT						m_ErrorMeshID;
	UINT						m_ErrorMaterialID;

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
	UINT						m_DeferredThreadGSize;

	//max number of instances, update this dynamically when we ovrrides one size, to beomce 1.5 the size?
	UINT						m_MaxNumOfInstances;
	ID3D11Buffer*				m_InstanceBuffer; //TODO Check if we want to split this into many buffers for each vertex group?
	XMFLOAT4X4*					m_MatriceList;

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

	//viewports + cameras
	std::vector<View>				m_View;


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

	//Create error resources
	HRESULT CreateErrorTexture();
	HRESULT CreateErrorMesh();
	HRESULT CreateErrorMaterial();




	//===============RESOURCES================\\

	UINT LoadTexture(std::string p_Name);





	//===========DRAW FUNCTIONS==============\\

	void SetMesh(MeshHandle* p_Handle);

	void SetMaterial(MaterialHandle* p_Handle);

	void DirectXGraphicEngine::SetTexture(UINT t_TextureID, UINT p_Slot);

	void SetShaderProgram(ShaderProgram* p_ShaderProgram);


	/*
	void SetShaders(ShaderProgram *p_Program);
	void SetTextures(RenderObject* p_Object);
	void SetPerFrameBuffers(std::vector<CameraStruct>* p_Cameras);
	HRESULT CreateRandomVectors();
	HRESULT Renderer::CreateOffsets();

	BOOL m_IsRendering;
	
	
	*/
	// todo move upp later
};

