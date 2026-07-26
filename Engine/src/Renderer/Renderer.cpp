#include "epch.h"
#include "Renderer.h"


Engine::Renderer::Renderer()
{
	//OnInit();
	instance = this;
}


Engine::Renderer::Renderer(float aspectratio)
{
	//OnInit(aspectratio);
	instance = this;
}

Engine::Renderer::~Renderer()
{
	
}


void Engine::Renderer::OnInit(float aspectratio /*= 1440.0f / 1080.0f*/)
{
	AspectRatio = aspectratio;

	FoV = XMConvertToRadians(90.0f);
	constantBuffer.Create(GraphicsContext::GetDevice(), &wvp);
	constantBuffer.BindVS(GraphicsContext::GetDeviceContext());

	InitPrimitives();

	vertexshader = VertexShader("src/Shaders/VertexShader.hlsl");
	pixelshader = PixelShader("src/Shaders/PixelShader.hlsl");

}

void Engine::Renderer::DrawPrimitive(const Primitives::Primitive& primitive)
{
	instance->DrawPrimitiveImpl(primitive);
}



void Engine::Renderer::DrawPrimitiveImpl(const Primitives::Primitive& primitive)
{
	switch (primitive.GetType())
	{
	case Primitives::PrimitiveType::Dot:
	{
		wvp = Camera::GetWorldViewProjection(primitive.GetWorldMatrix());

		constantBuffer.Update(GraphicsContext::GetDeviceContext(), &wvp);
		constantBuffer.BindVS(GraphicsContext::GetDeviceContext());

		GraphicsContext::GetDeviceContext()->IASetInputLayout(vertexshader.GetInputLayout().Get());

		GraphicsContext::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);
		UINT stride = sizeof(Primitives::Vertex);
		UINT offset = 0;
		pointvBuffer.BindBuffer(stride, offset);
		pointiBuffer.BindBuffer(DXGI_FORMAT_R16_UINT);
		vertexshader.Bind();
		pixelshader.Bind();
		GraphicsContext::GetDeviceContext()->DrawIndexed(primitive.GetIndexCount(), 0, 0);
		break;
	}
	case Primitives::PrimitiveType::Triangle:
	{
		wvp = Camera::GetWorldViewProjection(primitive.GetWorldMatrix());

		constantBuffer.Update(GraphicsContext::GetDeviceContext(), &wvp);
		constantBuffer.BindVS(GraphicsContext::GetDeviceContext());

		GraphicsContext::GetDeviceContext()->IASetInputLayout(vertexshader.GetInputLayout().Get());


		GraphicsContext::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
		UINT stride = sizeof(Primitives::Vertex);
		UINT offset = 0;
		trianglevBuffer.BindBuffer(stride, offset);
		triangleiBuffer.BindBuffer(DXGI_FORMAT_R16_UINT);
		vertexshader.Bind();
		pixelshader.Bind();
		GraphicsContext::GetDeviceContext()->DrawIndexed(primitive.GetIndexCount(), 0, 0);
		break;
	}
	case Primitives::PrimitiveType::Square:
	{
		wvp = Camera::GetWorldViewProjection(primitive.GetWorldMatrix());

		constantBuffer.Update(GraphicsContext::GetDeviceContext(), &wvp);
		constantBuffer.BindVS(GraphicsContext::GetDeviceContext());

		GraphicsContext::GetDeviceContext()->IASetInputLayout(vertexshader.GetInputLayout().Get());

		GraphicsContext::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		UINT stride = sizeof(Primitives::Vertex);
		UINT offset = 0;
		squarevBuffer.BindBuffer(stride, offset);
		squareiBuffer.BindBuffer(DXGI_FORMAT_R16_UINT);

		vertexshader.Bind();
		pixelshader.Bind();
		GraphicsContext::GetDeviceContext()->DrawIndexed(primitive.GetIndexCount(), 0, 0);
		break;
	}
	case Primitives::PrimitiveType::Cube:
	{
		wvp = Camera::GetWorldViewProjection(primitive.GetWorldMatrix());

		constantBuffer.Update(GraphicsContext::GetDeviceContext(), &wvp);
		constantBuffer.BindVS(GraphicsContext::GetDeviceContext());

		GraphicsContext::GetDeviceContext()->IASetInputLayout(vertexshader.GetInputLayout().Get());

		GraphicsContext::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		UINT stride = sizeof(Primitives::Vertex);
		UINT offset = 0;
		cubevBuffer.BindBuffer(stride, offset);
		cubeiBuffer.BindBuffer(DXGI_FORMAT_R16_UINT);
		vertexshader.Bind();
		pixelshader.Bind();
		GraphicsContext::GetDeviceContext()->DrawIndexed(primitive.GetIndexCount(), 0, 0);
		break;
	}
	}
}

void Engine::Renderer::DrawTriangle()
{
	instance->DrawTriangleImpl();
}


void Engine::Renderer::DrawTriangleImpl()
{
	wvp = Camera::GetWorldViewProjection(Primitives::triangle->GetWorldMatrix());

	constantBuffer.Update(GraphicsContext::GetDeviceContext(), &wvp);
	constantBuffer.BindVS(GraphicsContext::GetDeviceContext());

	GraphicsContext::GetDeviceContext()->IASetInputLayout(vertexshader.GetInputLayout().Get());

	GraphicsContext::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	UINT stride = sizeof(Primitives::Vertex);
	UINT offset = 0;
	trianglevBuffer.BindBuffer(stride, offset);
	triangleiBuffer.BindBuffer(DXGI_FORMAT_R16_UINT);
	vertexshader.Bind();
	pixelshader.Bind();
	GraphicsContext::GetDeviceContext()->DrawIndexed(Primitives::triangle->GetIndexCount(), 0, 0);
}

void Engine::Renderer::InitPrimitives()
{
	Primitives::star = CreateUnique<Primitives::Dot>();
	Primitives::triangle = CreateUnique<Primitives::Triangle>();
	Primitives::square = CreateUnique<Primitives::Square>();
	Primitives::cube = CreateUnique<Primitives::Cube>();

	pointvBuffer = VertexBuffer(Primitives::star->verts, sizeof(Primitives::Vertex), Primitives::star->GetVertexCount());
	trianglevBuffer = VertexBuffer(Primitives::triangle->verts, sizeof(Primitives::Vertex), Primitives::triangle->GetVertexCount());
	squarevBuffer = VertexBuffer(Primitives::square->verts, sizeof(Primitives::Vertex), Primitives::square->GetVertexCount());
	cubevBuffer = VertexBuffer(Primitives::cube->verts, sizeof(Primitives::Vertex), Primitives::cube->GetVertexCount());

	pointiBuffer = IndexBuffer(Primitives::star->indices, sizeof(uint16_t), Primitives::star->GetIndexCount());
	triangleiBuffer = IndexBuffer(Primitives::triangle->indices, sizeof(uint16_t), Primitives::triangle->GetIndexCount());
	squareiBuffer = IndexBuffer(Primitives::square->indices, sizeof(uint16_t), Primitives::square->GetIndexCount());
	cubeiBuffer = IndexBuffer(Primitives::cube->indices, sizeof(uint16_t), Primitives::cube->GetIndexCount());

}


Engine::Renderer* Engine::Renderer::instance = nullptr;
