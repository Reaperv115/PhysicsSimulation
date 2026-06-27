#pragma once
#include <d3d11.h>
#include <wrl.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")

#include "../renderer/Primitives.h"
#include "../Camera/Camera.h"

using namespace Microsoft::WRL;
using namespace DirectX;


namespace Engine
{
	class Graphics
	{
	public:
		Graphics();
		~Graphics();

		void InitGraphics(HWND windowhandle, float width, float height);
		void InitPipeline();
		void PrepareScene();
		void PresentScene();

		void CreateInputLayoutAndLoadShaders();
		void CreateShaders();

		std::filesystem::path GetExeFolder();

		inline ComPtr<ID3D11Device>& GetDevice() { return _device; }
		inline ComPtr<ID3D11DeviceContext>& GetDeviceContext() { return deviceContext; }
		inline ComPtr<ID3D11VertexShader>& GetVertexShader()  { return vertexShader; }
		inline ComPtr<ID3D11PixelShader>& GetPixelShader() { return pixelShader; }
		inline ComPtr<ID3D11RenderTargetView>& GetRenderTargetView() { return renderTargetView; }
		inline ComPtr<ID3D11DepthStencilView>& GetDepthStencilView() { return depthStencilView; }
		inline ComPtr<ID3D11InputLayout>& GetInputLayout() { return inputlayOut; }
		inline float GetWidth() const { return f_width; }
		inline float GetHeight() const { return f_height; }
		

	private:
		ComPtr<ID3D11Device> _device;
		ComPtr<IDXGIDevice> idxgiDevice;
		ComPtr<ID3D11DeviceContext> deviceContext;
		ComPtr<IDXGISwapChain> swapChain;
		ComPtr<IDXGIFactory> _factory;
		ComPtr<ID3D11Texture2D> backBuffer;
		ComPtr<ID3D11RenderTargetView> renderTargetView;
		ComPtr<ID3D11InputLayout> inputlayOut;
		ComPtr<ID3DBlob> vsBlob;
		ComPtr<ID3DBlob> psBlob;
		ComPtr<ID3DBlob> errorBlob;

		ComPtr<ID3D11PixelShader> pixelShader;
		ComPtr<ID3D11VertexShader> vertexShader;
		ComPtr<ID3D11Texture2D> zBuffer;
		ComPtr<ID3D11DepthStencilView> depthStencilView;
		ComPtr<ID3D11RasterizerState> rasterizerState;
		D3D11_VIEWPORT viewPort;

		float time = 0.0f;
		float speed = 2.0f;
		float otherspeed = 40.0f;
		float f_width, f_height;

		

		


	};
}

