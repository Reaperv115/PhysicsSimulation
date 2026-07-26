#pragma once
#include <d3d11.h>
#include <wrl.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>

#include "GraphicsContext.h"

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
		void PrepareScene();
		void PresentScene();


		std::filesystem::path GetExeFolder();

		
		inline ComPtr<ID3D11RenderTargetView>& GetRenderTargetView() { return renderTargetView; }
		inline ComPtr<ID3D11DepthStencilView>& GetDepthStencilView() { return depthStencilView; }
		inline float GetWidth() const { return f_width; }
		inline float GetHeight() const { return f_height; }
		inline float GetAspectRatio() const { return f_width / f_height; }
		inline void UpdateContext(const Shared<GraphicsContext>& graphicscontext) { graphicsContext = graphicscontext; }
		

	private:
		ComPtr<ID3D11Texture2D> backBuffer;
		ComPtr<ID3D11RenderTargetView> renderTargetView;

		ComPtr<ID3D11Texture2D> zBuffer;
		ComPtr<ID3D11DepthStencilView> depthStencilView;
		D3D11_VIEWPORT viewPort;

		Shared<GraphicsContext> graphicsContext;

		float time = 0.0f;
		float speed = 2.0f;
		float otherspeed = 40.0f;
		float f_width, f_height;

		

		


	};
}

