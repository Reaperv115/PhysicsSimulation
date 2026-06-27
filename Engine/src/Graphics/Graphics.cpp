#include "epch.h"
#include "Graphics.h"

Engine::Graphics::Graphics()
{
	
}

Engine::Graphics::~Graphics()
{

}

void Engine::Graphics::InitGraphics(HWND windowhandle, float width, float height)
{
	f_width = width;
	f_height = height;

	DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
	swapChainDesc.BufferCount = 2;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.BufferDesc.Width = f_width;
	swapChainDesc.BufferDesc.Height = f_height;
	swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
	swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL;
	swapChainDesc.OutputWindow = windowhandle;
	swapChainDesc.Windowed = TRUE;

	UINT deviceFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT | D3D11_CREATE_DEVICE_DEBUG;
	D3D_FEATURE_LEVEL featureLevel = {  };
	HRESULT hr = D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, NULL, deviceFlags, nullptr, NULL, D3D11_SDK_VERSION, &_device, nullptr, &deviceContext);
	if (hr != S_OK)
	{
		throw std::runtime_error("Failed to create D3D11 device");
	}

	// creating factory and swapchain
	_device.As(&idxgiDevice);

	ComPtr<IDXGIAdapter> adapter;
	idxgiDevice->GetAdapter(&adapter);
	adapter->GetParent(__uuidof(IDXGIFactory), reinterpret_cast<void**>(_factory.GetAddressOf()));
	hr = _factory->CreateSwapChain(idxgiDevice.Get(), &swapChainDesc, &swapChain);
	if (hr != S_OK)
	{
		throw std::runtime_error("Failed to create swap chain");
	}

	// creating back-buffer
	swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), &backBuffer);

	D3D11_TEXTURE2D_DESC zbufferDesc = {  };
	zbufferDesc.Width = width;
	zbufferDesc.Height = height;
	zbufferDesc.MipLevels = 1;
	zbufferDesc.ArraySize = 1;
	zbufferDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	zbufferDesc.SampleDesc.Count = 1;
	zbufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	_device->CreateTexture2D(&zbufferDesc, nullptr, &zBuffer);

	D3D11_DEPTH_STENCIL_VIEW_DESC depthstencilviewDesc;
	ZeroMemory(&depthstencilviewDesc, sizeof(depthstencilviewDesc));
	depthstencilviewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	_device->CreateDepthStencilView(zBuffer.Get(), &depthstencilviewDesc, &depthStencilView);

	// setting up viewport
	viewPort.TopLeftX = 0.0f;
	viewPort.TopLeftY = 0.0f;
	viewPort.Width = width;
	viewPort.Height = height;
	viewPort.MinDepth = 0.0f;
	viewPort.MaxDepth = 1.0f;
	deviceContext->RSSetViewports(1, &viewPort);

	// creating render-target-view
	_device->CreateRenderTargetView(backBuffer.Get(), nullptr, &renderTargetView);

	InitPipeline();
}

void Engine::Graphics::InitPipeline()
{
	CreateInputLayoutAndLoadShaders();
	CreateShaders();

	// creating rasterizer state
	D3D11_RASTERIZER_DESC rasterizerDesc = {};
	rasterizerDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
	rasterizerDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_NONE;
	rasterizerDesc.FrontCounterClockwise = false;
	HRESULT hr = _device->CreateRasterizerState(&rasterizerDesc, &rasterizerState);
	if (hr != S_OK)
	{
		throw std::runtime_error("Failed to create rasterizer state");
	}
	else
	{
		deviceContext->RSSetState(rasterizerState.Get());
	}

	
}
void Engine::Graphics::CreateInputLayoutAndLoadShaders()
{
	// TODO: make relative path variable work
	HRESULT hr;

	// creating input-layout
	D3D11_INPUT_ELEMENT_DESC inputlayout[] =
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};

	auto exeFolder = GetExeFolder();
	std::filesystem::path shaderpath = L"src/Shaders/VertexShader.hlsl";
	UINT vscompilerFlags = D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
	hr = D3DCompileFromFile(shaderpath.wstring().c_str(), nullptr, nullptr, "main", "vs_5_0", vscompilerFlags, 0, vsBlob.GetAddressOf(), &errorBlob);
	if (FAILED(hr))
	{
		if (errorBlob)
		{
			std::string msg(static_cast<const char*>(errorBlob->GetBufferPointer()), errorBlob->GetBufferSize());
			OutputDebugStringA(("Vertex shader compile error: " + msg + "\n").c_str());
		}
		else
		{
			char buf[512];
			FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, nullptr, hr, 0, buf, (DWORD)std::size(buf), nullptr);
			OutputDebugStringA(("D3DCompileFromFile failed: " + std::string(buf) + "\n").c_str());
		}
		throw std::runtime_error("Failed to compile vertex shader");
	}
	hr = _device->CreateInputLayout(inputlayout, 2, vsBlob->GetBufferPointer(), vsBlob->GetBufferSize(), inputlayOut.GetAddressOf());
	if (FAILED(hr))
	{
		throw std::runtime_error("Failed to create input layout");
	}

	shaderpath = L"src/Shaders/PixelShader.hlsl";
	hr = D3DCompileFromFile(shaderpath.wstring().c_str(), nullptr, nullptr, "main", "ps_5_0", 0, 0, &psBlob, nullptr);
	if (hr != S_OK)
		throw std::runtime_error("Failed to compile pixel shader");
}

void Engine::Graphics::CreateShaders()
{
	HRESULT hr;
	// create pixel shader
	hr = _device->CreatePixelShader(psBlob->GetBufferPointer(), psBlob->GetBufferSize(), nullptr, &pixelShader);
	if (hr != S_OK)
	{
		throw std::runtime_error("Failed to create pixel shader");
	}

	// create vertex shader
	hr = _device->CreateVertexShader(vsBlob->GetBufferPointer(), vsBlob->GetBufferSize(), nullptr, &vertexShader);
	if (hr != S_OK)
	{
		throw std::runtime_error("Failed to create vertex shader");
	}
}


std::filesystem::path Engine::Graphics::GetExeFolder()
{
	wchar_t buffer[MAX_PATH];
	GetModuleFileNameW(nullptr, buffer, MAX_PATH);
	return std::filesystem::path(buffer).parent_path();
}

void Engine::Graphics::PrepareScene()
{
	deviceContext->OMSetRenderTargets(1, renderTargetView.GetAddressOf(), depthStencilView.Get());

	float color[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
	deviceContext->ClearRenderTargetView(renderTargetView.Get(), color);

	deviceContext->ClearDepthStencilView(depthStencilView.Get(), D3D11_CLEAR_DEPTH, 1.0f, 0.0f);
	deviceContext->RSSetState(rasterizerState.Get());
	
}

void Engine::Graphics::PresentScene()
{
	swapChain->Present(1, 0);
}
