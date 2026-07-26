#pragma once
#include <d3d11.h>
#include <DirectXMath.h>
#include <wrl.h>
#include <print>

#pragma comment(lib, "d3d11.lib")

using namespace Microsoft::WRL;
using namespace DirectX;

namespace Engine
{
	class GraphicsContext
	{
	public:
		GraphicsContext();
		GraphicsContext(HWND hwnd, float width, float height);
		~GraphicsContext();

	public:
		bool Initialize(HWND hwnd, float width, float height);
		bool CreateDeviceAndContext();
		bool CreateSwapChain(HWND hwnd, float width, float height);
		void CreateRasterizerState();

		inline static ComPtr<ID3D11Device>& GetDevice() { return _device; }
		inline static ComPtr<ID3D11DeviceContext>& GetDeviceContext() { return deviceContext; }
		inline static ComPtr<IDXGISwapChain>& GetSwapChain() { return swapChain; }
		inline static ComPtr<ID3D11RasterizerState>& GetRasterizerState() { return rasterizerState; }
		inline GraphicsContext* GetGraphicsContext() { return this; }

	private:
		static ComPtr<ID3D11Device> _device;
		static ComPtr<ID3D11DeviceContext> deviceContext;
		static ComPtr<IDXGISwapChain> swapChain;
		static ComPtr<ID3D11RasterizerState> rasterizerState;

	};
}