#include "epch.h"
#include "GraphicsContext.h"



Engine::GraphicsContext::GraphicsContext(HWND hwnd, float width, float height)
{
	if (!Initialize(hwnd, width, height))
	{
		throw std::runtime_error("Failed to initialize Graphics Context");
	}
}

Engine::GraphicsContext::GraphicsContext()
{

}

Engine::GraphicsContext::~GraphicsContext()
{
	
}

bool Engine::GraphicsContext::Initialize(HWND hwnd, float width, float height)
{
	if (!CreateDeviceAndContext())
	{
		std::println("Failed to create device and device context");
		return false;
	}
	if (!CreateSwapChain(hwnd, width, height))
	{
		std::println("Failed to create swapchain");
		return false;
	}

	CreateRasterizerState();
	return true;
}

bool Engine::GraphicsContext::CreateDeviceAndContext()
{
	UINT deviceFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT | D3D11_CREATE_DEVICE_DEBUG;
	D3D_FEATURE_LEVEL featureLevel = {  };
	HRESULT hr = D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, NULL, deviceFlags, nullptr, NULL, D3D11_SDK_VERSION, &_device, nullptr, &deviceContext);
	if (hr != S_OK)
	{
		throw std::runtime_error("Failed to create D3D11 device");
		return false;
	}
	return true;
}

bool Engine::GraphicsContext::CreateSwapChain(HWND hwnd, float width, float height)
{
	DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
	swapChainDesc.BufferCount = 2;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.BufferDesc.Width = width;
	swapChainDesc.BufferDesc.Height = height;
	swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
	swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL;
	swapChainDesc.OutputWindow = hwnd;
	swapChainDesc.Windowed = TRUE;

	ComPtr<IDXGIFactory> factory;
	CreateDXGIFactory(__uuidof(IDXGIFactory), reinterpret_cast<void**>(factory.GetAddressOf()));
	HRESULT hr = factory->CreateSwapChain(_device.Get(), &swapChainDesc, swapChain.GetAddressOf());
	if (hr != S_OK)
	{
		throw std::runtime_error("Failed to create swap chain");
		return false;
	}
	return true;
}

void Engine::GraphicsContext::CreateRasterizerState()
{
	D3D11_RASTERIZER_DESC rasterizerdesc = { };
	rasterizerdesc.FillMode = D3D11_FILL_SOLID;
	rasterizerdesc.CullMode = D3D11_CULL_NONE;
	GraphicsContext::GetDevice()->CreateRasterizerState(&rasterizerdesc, rasterizerState.GetAddressOf());
}

ComPtr<ID3D11Device> Engine::GraphicsContext::_device = nullptr;
ComPtr<ID3D11DeviceContext> Engine::GraphicsContext::deviceContext = nullptr;
ComPtr<IDXGISwapChain> Engine::GraphicsContext::swapChain = nullptr;
ComPtr<ID3D11RasterizerState> Engine::GraphicsContext::rasterizerState = nullptr;
