#include "Renderer.h"

Renderer* Renderer::m_Singleton = nullptr;

Renderer* Renderer::GetInstance()
{
	if (m_Singleton == nullptr)
	{
		m_Singleton = new Renderer();
	}
	return m_Singleton;
}

Renderer::Renderer()
{
	m_Height = new UINT();
	m_Width = new UINT();
	*m_Height = 0;
	*m_Width = 0;
}


Renderer::~Renderer()
{
}

bool Renderer::Initialize(UINT p_Width, UINT p_Height, HWND p_HandleWindow)
{
	HRESULT hr = S_OK;

	*m_Height = p_Height;
	*m_Width = p_Width;

	hr = InitializeDriverAndVersion(p_HandleWindow);
	if( FAILED( hr ) )
		return false;


	return true;
}


HRESULT Renderer::InitializeDriverAndVersion(HWND p_HandleWindow)
{
	HRESULT hr = S_OK;

	UINT createDeviceFlags = 0;
#ifdef _DEBUG
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	D3D_DRIVER_TYPE driverTypes[] =
	{
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_REFERENCE,
	};
	UINT numDriverTypes = ARRAYSIZE(driverTypes);

	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
	};
	UINT numFeatureLevels = ARRAYSIZE(featureLevels);

	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.BufferCount = 1;
	sd.BufferDesc.Width = *m_Width;
	sd.BufferDesc.Height = *m_Height;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT | DXGI_USAGE_UNORDERED_ACCESS; //fixed for deferred rendering, set flag for input if want to put into a shader as well I guess
	sd.OutputWindow = p_HandleWindow;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.Windowed = TRUE;
	sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	for (UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++)
	{
		m_DriverType = driverTypes[driverTypeIndex];
		hr = D3D11CreateDeviceAndSwapChain(
			nullptr,
			m_DriverType,
			nullptr,
			createDeviceFlags,
			featureLevels,
			numFeatureLevels,
			D3D11_SDK_VERSION,
			&sd,
			&m_SwapChain,
			&m_Device,
			&m_FeatureLevel,
			&m_DeviceContext);

		if (hr == E_INVALIDARG)
		{
			// DirectX 11.0 platforms will not recognize D3D_FEATURE_LEVEL_11_1 so we need to retry without it
			hr = D3D11CreateDeviceAndSwapChain(
				nullptr,
				m_DriverType,
				nullptr,
				createDeviceFlags,
				&featureLevels[1],
				numFeatureLevels - 1,
				D3D11_SDK_VERSION, &sd,
				&m_SwapChain,
				&m_Device,
				&m_FeatureLevel,
				&m_DeviceContext);
		}

		if (SUCCEEDED(hr))
			break;
	}
	if (FAILED(hr))
		return hr;

	// Obtain the Direct3D 11.1 versions if available
	hr = m_Device->QueryInterface(__uuidof(ID3D11Device1), reinterpret_cast<void**>(&m_Device1));
	if (SUCCEEDED(hr))
	{
		(void)m_DeviceContext->QueryInterface(__uuidof(ID3D11DeviceContext1), reinterpret_cast<void**>(&m_DeviceContext1));
	}
	return hr;
}

HRESULT Renderer::InitializeRenderTargetView()
{
	HRESULT hr = S_OK;

	ID3D11Texture2D* t_BackBuffer = nullptr;
	hr = m_SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&t_BackBuffer);
	if (FAILED(hr))
		return hr;

	hr = m_Device->CreateRenderTargetView(t_BackBuffer, nullptr, &m_RenderTargetView);
	if (FAILED(hr))
		return hr;

	hr = m_Device->CreateUnorderedAccessView(t_BackBuffer, nullptr, &m_BackBufferUAV);
	if (FAILED(hr))
		return hr;

	t_BackBuffer->Release();


	return hr;
}