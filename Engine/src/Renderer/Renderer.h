#pragma once
#include "../Graphics/Graphics.h"
#include "../Camera/Camera.h"
#include "Primitives.h"
#include "../ConstantBuffer/ConstantBuffer.h"
#include "Core.h"

namespace Engine
{
	class Renderer
	{
	public:
		Renderer();
		Renderer(Unique<Graphics>& graphics);
		~Renderer();

		void OnInit();

		static void DrawPrimitive(const Primitives::Primitive& primitive);
		static void DrawTriangle();
		static void SetInstance(Renderer* renderer);

		void CreateVertexBuffer(void* data, UINT elementbyteSize, int numElements, ComPtr<ID3D11Buffer>& outBuffer);
		void CreateIndexBuffer(void* data, UINT elementbyteSize, int numElements, ComPtr<ID3D11Buffer>& outBuffer);
		void DrawPrimitiveImpl(const Primitives::Primitive& primitive);
		void DrawTriangleImpl();

		inline XMMATRIX GetWorldMatrix() const { return worldMatrix; }
		inline XMMATRIX GetViewMatrix() const { return viewMatrix; }
		inline XMMATRIX GetProjectionMatrix() const { return projectionMatrix; }
		inline float GetFOV() const { return FoV; }
		inline float GetAspectRatio() const { return AspectRatio; }

		inline Unique<Graphics>& GetGraphics() { return gfx; }
		inline Unique<Camera>& GetCamera() { return camera; }

		static Renderer* GetInstance();
	private:
		void InitPrimitives();
	private:
		Unique<Graphics> gfx;
		Unique<Camera> camera;

		static Renderer* instance;

		static XMMATRIX worldMatrix;
		static XMMATRIX viewMatrix;
		static XMMATRIX projectionMatrix;

		ComPtr<ID3D11Buffer> pointindexBuffer;
		D3D11_BUFFER_DESC pointindexbufferDesc = { 0 };
		D3D11_SUBRESOURCE_DATA pointindexbufferData = {0};

		ComPtr<ID3D11Buffer> triangleindexBuffer;
		D3D11_BUFFER_DESC triangleindexbuffDesc = { 0 };
		D3D11_SUBRESOURCE_DATA triangleindexbufferData = { 0 };

		ComPtr<ID3D11Buffer> squareindexBuffer;
		D3D11_BUFFER_DESC squareindexbuffDesc = { 0 };
		D3D11_SUBRESOURCE_DATA sqaureindexbufferData = { 0 };

		ComPtr<ID3D11Buffer> cubeindexBuffer;
		D3D11_BUFFER_DESC cubeindexbufferDesc = { 0 };
		D3D11_SUBRESOURCE_DATA cubeindexbufferData = { 0 };

		ComPtr<ID3D11Buffer> vertexBuffer;
		D3D11_BUFFER_DESC bufferDesc = { 0 };
		D3D11_SUBRESOURCE_DATA bufferData = { 0 };

		D3D11_SUBRESOURCE_DATA matrixBufferData = {0};
		D3D11_BUFFER_DESC matrixBufferDesc = {0};
		D3D11_MAPPED_SUBRESOURCE mappedsubResource;
		XMMATRIX wvpMatrix;
		XMMATRIX rotationMatrix, modelMatrix;
		float nearZ = 0.1f;
		float farZ = 100.0f;
		float FoV;
		float AspectRatio;

		ConstantBuffer<XMFLOAT4X4> constantBuffer;
		XMFLOAT4X4 wvp;

		ComPtr<ID3D11Buffer> pointBuffer;
		ComPtr<ID3D11Buffer> triangleBuffer;
		ComPtr<ID3D11Buffer> squareBuffer;
		ComPtr<ID3D11Buffer> cubeBuffer;
		
		
	};
}

