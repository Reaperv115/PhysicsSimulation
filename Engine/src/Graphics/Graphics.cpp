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

	graphicsContext = CreateShared<GraphicsContext>(windowhandle, width, height);

	// creating back-buffer
	GraphicsContext::GetSwapChain()->GetBuffer(0, __uuidof(ID3D11Texture2D), &backBuffer);

	D3D11_TEXTURE2D_DESC zbufferDesc = {  };
	zbufferDesc.Width = width;
	zbufferDesc.Height = height;
	zbufferDesc.MipLevels = 1;
	zbufferDesc.ArraySize = 1;
	zbufferDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	zbufferDesc.SampleDesc.Count = 1;
	zbufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	GraphicsContext::GetDevice()->CreateTexture2D(&zbufferDesc, nullptr, &zBuffer);

	D3D11_DEPTH_STENCIL_VIEW_DESC depthstencilviewDesc;
	ZeroMemory(&depthstencilviewDesc, sizeof(depthstencilviewDesc));
	depthstencilviewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	GraphicsContext::GetDevice()->CreateDepthStencilView(zBuffer.Get(), &depthstencilviewDesc, &depthStencilView);

	// setting up viewport
	viewPort.TopLeftX = 0.0f;
	viewPort.TopLeftY = 0.0f;
	viewPort.Width = width;
	viewPort.Height = height;
	viewPort.MinDepth = 0.0f;
	viewPort.MaxDepth = 1.0f;
	GraphicsContext::GetDeviceContext()->RSSetViewports(1, &viewPort);

	// creating render-target-view
	GraphicsContext::GetDevice()->CreateRenderTargetView(backBuffer.Get(), nullptr, &renderTargetView);

	// TODO: resource logging
	ComPtr<ID3D11InfoQueue> infoqueue;
	GraphicsContext::GetDevice()->QueryInterface(__uuidof(ID3D11InfoQueue), (void**)infoqueue.GetAddressOf());

	if (infoqueue)
	{
		infoqueue->SetBreakOnSeverity(D3D11_MESSAGE_SEVERITY_WARNING, true);

		UINT64 numberMessages = infoqueue->GetNumStoredMessages();
		for (UINT64 i = 0; i < numberMessages; i++)
		{
			size_t messageSize = 0;
			infoqueue->GetMessage(i, nullptr, &messageSize);

			D3D11_MESSAGE* message = (D3D11_MESSAGE*)malloc(messageSize);
			infoqueue->GetMessage(i, message, &messageSize);

			OutputDebugStringA((std::string(message->pDescription) + "\n").c_str());
			free(message);
		}
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
	GraphicsContext::GetDeviceContext()->OMSetRenderTargets(1, renderTargetView.GetAddressOf(), depthStencilView.Get());

	float color[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
	GraphicsContext::GetDeviceContext()->ClearRenderTargetView(renderTargetView.Get(), color);

	GraphicsContext::GetDeviceContext()->ClearDepthStencilView(depthStencilView.Get(), D3D11_CLEAR_DEPTH, 1.0f, 0.0f);
	GraphicsContext::GetDeviceContext()->RSSetState(GraphicsContext::GetRasterizerState().Get());
	
}

void Engine::Graphics::PresentScene()
{
	GraphicsContext::GetSwapChain()->Present(1, 0);
}
