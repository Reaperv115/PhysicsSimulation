#pragma once
#include <d3d11.h>
#include <wrl.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>
#include "DDSTextureLoader11.h"

#include "../Primitives.h"
#include "../VertexBuffer.h"
#include "../IndexBuffer.h"
#include "../../ConstantBuffer/ConstantBuffer.h"
#include "../../Graphics/GraphicsContext.h"
#include "../../Shaders/VertexShader.h"
#include "../../Shaders/PixelShader.h"

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")

using namespace Microsoft::WRL;
using namespace DirectX;

namespace Engine
{
	class SkyBox
	{
	public: SkyBox();
		  ~SkyBox();

		  void Init();
		  void Render();

	private:
		ComPtr<ID3D11Texture2D> skyboxtexture;
		ComPtr<ID3D11Buffer> skyboxbuffer;

		VertexBuffer vertexBuffer;
		IndexBuffer indexBuffer;
		ConstantBuffer<XMFLOAT4X4> constantBuffer;
		VertexShader vertexshader;
		PixelShader pixelshader;

		XMFLOAT4X4 worldmatrix;

		Primitives::Vertex verts[24];
		uint16_t indices[36] =
		{
			0, 1, 2, 2, 1, 3,       // Front face
			4, 5, 6, 6, 5, 7,       // Back face
			8, 9, 10, 10, 9, 11,    // Left face
			12, 13, 14, 14, 13, 15, // Right face
			16, 17, 18, 18, 17, 19, // Top face
			20, 21, 22, 22, 21, 23  // Bottom face
		};
	};
}