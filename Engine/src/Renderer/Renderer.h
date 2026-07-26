#pragma once
#include "../Graphics/Graphics.h"
#include "../Graphics/GraphicsContext.h"
#include "../Camera/Camera.h"
#include "Primitives.h"
#include "../ConstantBuffer/ConstantBuffer.h"
#include "Core.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "../Shaders/VertexShader.h"
#include "../Shaders/PixelShader.h"

namespace Engine
{
	class Renderer
	{
	public:
		Renderer();
		Renderer(float aspectratio);
		~Renderer();


		void OnInit(float aspectratio = 1440.0f / 1080.0f);
		static void DrawPrimitive(const Primitives::Primitive& primitive);
		void DrawPrimitiveImpl(const Primitives::Primitive& primitive);
		static void DrawTriangle();
		void DrawTriangleImpl();

		inline float GetFOV() const { return FoV; }
		inline float GetAspectRatio() const { return AspectRatio; }
	private:
		void InitPrimitives();
	private:
		static Renderer* instance;

		float FoV;
		float AspectRatio;

		ConstantBuffer<XMFLOAT4X4> constantBuffer;
		XMFLOAT4X4 wvp;


		VertexBuffer pointvBuffer;
		VertexBuffer trianglevBuffer;
		VertexBuffer squarevBuffer;
		VertexBuffer cubevBuffer;

		IndexBuffer pointiBuffer;
		IndexBuffer triangleiBuffer;
		IndexBuffer squareiBuffer;
		IndexBuffer cubeiBuffer;
		
		VertexShader vertexshader;
		PixelShader pixelshader;
	};
}

