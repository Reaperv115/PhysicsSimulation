#include "epch.h"
#include "Renderer.h"


Engine::Renderer::Renderer()
{

}


Engine::Renderer::Renderer(Unique<Graphics>& graphics)
	:gfx(std::move(graphics))
{
	if (!instance)
		instance = this;


	FoV = XMConvertToRadians(90.0f);
	OnInit();
}

Engine::Renderer::~Renderer()
{
	
}

void Engine::Renderer::OnInit()
{
	if (!gfx)
		throw std::runtime_error("Graphics pointer is null in Renderer::OnInit");

	
	constantBuffer.Create(gfx->GetDevice(), &wvp);
	constantBuffer.BindVS(gfx->GetDeviceContext());

	InitPrimitives();

	camera = CreateUnique<Camera>(FoV, gfx->GetWidth()/gfx->GetHeight());


}

void Engine::Renderer::CreateVertexBuffer(void* data, UINT elementbyteSize, int numElements, ComPtr<ID3D11Buffer>& outBuffer)
{
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferDesc.ByteWidth = elementbyteSize * numElements;
	bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	bufferData.pSysMem = data;
	gfx->GetDevice()->CreateBuffer(&bufferDesc, data ? &bufferData : nullptr, outBuffer.GetAddressOf());
}

void Engine::Renderer::CreateIndexBuffer(void* data, UINT elementbyteSize, int numElements, ComPtr<ID3D11Buffer>& outBuffer)
{
	bufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bufferDesc.ByteWidth = elementbyteSize * numElements;
	bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	bufferDesc.MiscFlags = 0;
	bufferDesc.StructureByteStride = 0;

	bufferData.pSysMem = data;
	gfx->GetDevice()->CreateBuffer(&bufferDesc, data ? &bufferData : nullptr, outBuffer.GetAddressOf());
}

void Engine::Renderer::DrawPrimitiveImpl(const Primitives::Primitive& primitive)
{
	switch (primitive.GetType())
	{
	case Primitives::PrimitiveType::Dot:
	{
		wvp = camera->GetMVP(primitive.GetWorldMatrix());

		constantBuffer.Update(gfx->GetDeviceContext(), &wvp);
		constantBuffer.BindVS(gfx->GetDeviceContext());

		gfx->GetDeviceContext()->IASetInputLayout(gfx->GetInputLayout().Get());


		gfx->GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);
		UINT stride = sizeof(Primitives::Vertex);
		UINT offset = 0;
		gfx->GetDeviceContext()->IASetVertexBuffers(0, 1, pointBuffer.GetAddressOf(), &stride, &offset);
		gfx->GetDeviceContext()->IASetIndexBuffer(pointindexBuffer.Get(), DXGI_FORMAT_R16_UINT, 0);
		gfx->GetDeviceContext()->VSSetShader(gfx->GetVertexShader().Get(), nullptr, 0);
		gfx->GetDeviceContext()->PSSetShader(gfx->GetPixelShader().Get(), nullptr, 0);
		gfx->GetDeviceContext()->DrawIndexed(primitive.GetIndexCount(), 0, 0);
		break;
	}
	case Primitives::PrimitiveType::Triangle:
	{
		wvp = camera->GetMVP(primitive.GetWorldMatrix());

		constantBuffer.Update(gfx->GetDeviceContext(), &wvp);
		constantBuffer.BindVS(gfx->GetDeviceContext());

		gfx->GetDeviceContext()->IASetInputLayout(gfx->GetInputLayout().Get());


		gfx->GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
		UINT stride = sizeof(Primitives::Vertex);
		UINT offset = 0;
		gfx->GetDeviceContext()->IASetVertexBuffers(0, 1, triangleBuffer.GetAddressOf(), &stride, &offset);
		gfx->GetDeviceContext()->IASetIndexBuffer(triangleindexBuffer.Get(), DXGI_FORMAT_R16_UINT, 0);
		gfx->GetDeviceContext()->VSSetShader(gfx->GetVertexShader().Get(), nullptr, 0);
		gfx->GetDeviceContext()->PSSetShader(gfx->GetPixelShader().Get(), nullptr, 0);
		gfx->GetDeviceContext()->DrawIndexed(primitive.GetIndexCount(), 0, 0);
		break;
	}
	case Primitives::PrimitiveType::Square:
	{
		wvp = camera->GetMVP(primitive.GetWorldMatrix());

		constantBuffer.Update(gfx->GetDeviceContext(), &wvp);
		constantBuffer.BindVS(gfx->GetDeviceContext());

		gfx->GetDeviceContext()->IASetInputLayout(gfx->GetInputLayout().Get());


		gfx->GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
		UINT stride = sizeof(Primitives::Vertex);
		UINT offset = 0;
		gfx->GetDeviceContext()->IASetVertexBuffers(0, 1, squareBuffer.GetAddressOf(), &stride, &offset);
		gfx->GetDeviceContext()->IASetIndexBuffer(squareindexBuffer.Get(), DXGI_FORMAT_R16_UINT, 0);
		gfx->GetDeviceContext()->VSSetShader(gfx->GetVertexShader().Get(), nullptr, 0);
		gfx->GetDeviceContext()->PSSetShader(gfx->GetPixelShader().Get(), nullptr, 0);
		gfx->GetDeviceContext()->DrawIndexed(primitive.GetIndexCount(), 0, 0);
		break;
	}
	case Primitives::PrimitiveType::Cube:
	{
		wvp = camera->GetMVP(primitive.GetWorldMatrix());

		constantBuffer.Update(gfx->GetDeviceContext(), &wvp);
		constantBuffer.BindVS(gfx->GetDeviceContext());

		gfx->GetDeviceContext()->IASetInputLayout(gfx->GetInputLayout().Get());


		gfx->GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		UINT stride = sizeof(Primitives::Vertex);
		UINT offset = 0;
		gfx->GetDeviceContext()->IASetVertexBuffers(0, 1, cubeBuffer.GetAddressOf(), &stride, &offset);
		gfx->GetDeviceContext()->IASetIndexBuffer(cubeindexBuffer.Get(), DXGI_FORMAT_R16_UINT, 0);
		gfx->GetDeviceContext()->VSSetShader(gfx->GetVertexShader().Get(), nullptr, 0);
		gfx->GetDeviceContext()->PSSetShader(gfx->GetPixelShader().Get(), nullptr, 0);
		gfx->GetDeviceContext()->DrawIndexed(primitive.GetIndexCount(), 0, 0);
		break;
	}
	}
}

void Engine::Renderer::DrawTriangleImpl()
{
	wvp = camera->GetMVP(Primitives::triangle->GetWorldMatrix());

	constantBuffer.Update(gfx->GetDeviceContext(), &wvp);
	constantBuffer.BindVS(gfx->GetDeviceContext());

	gfx->GetDeviceContext()->IASetInputLayout(gfx->GetInputLayout().Get());


	gfx->GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	UINT stride = sizeof(Primitives::Vertex);
	UINT offset = 0;
	gfx->GetDeviceContext()->IASetVertexBuffers(0, 1, triangleBuffer.GetAddressOf(), &stride, &offset);
	gfx->GetDeviceContext()->IASetIndexBuffer(triangleindexBuffer.Get(), DXGI_FORMAT_R16_UINT, 0);
	gfx->GetDeviceContext()->VSSetShader(gfx->GetVertexShader().Get(), nullptr, 0);
	gfx->GetDeviceContext()->PSSetShader(gfx->GetPixelShader().Get(), nullptr, 0);
	gfx->GetDeviceContext()->DrawIndexed(Primitives::triangle->GetIndexCount(), 0, 0);
}

Engine::Renderer* Engine::Renderer::GetInstance()
{
	return instance;
}

void Engine::Renderer::InitPrimitives()
{
	Primitives::star = CreateUnique<Primitives::Dot>();
	Primitives::triangle = CreateUnique<Primitives::Triangle>();
	Primitives::square = CreateUnique<Primitives::Square>();
	Primitives::cube = CreateUnique<Primitives::Cube>();

	if (gfx)
	{
		CreateVertexBuffer(Primitives::star->verts, sizeof(Primitives::Vertex), Primitives::star->GetVertexCount(), pointBuffer);
		CreateVertexBuffer(Primitives::triangle->verts, sizeof(Primitives::Vertex), Primitives::triangle->GetVertexCount(), triangleBuffer);
		CreateVertexBuffer(Primitives::square->verts, sizeof(Primitives::Vertex), Primitives::square->GetVertexCount(), squareBuffer);
		CreateVertexBuffer(Primitives::cube->vertices, sizeof(Primitives::Vertex), Primitives::cube->GetVertexCount(), cubeBuffer);

		CreateIndexBuffer(Primitives::triangle->indices, sizeof(uint16_t), Primitives::triangle->GetIndexCount(), triangleindexBuffer);
		CreateIndexBuffer(Primitives::square->indices, sizeof(uint16_t), Primitives::square->GetIndexCount(), squareindexBuffer);
		CreateIndexBuffer(Primitives::cube->indices, sizeof(uint16_t), Primitives::cube->GetIndexCount(), cubeindexBuffer);
		CreateIndexBuffer(Primitives::star->indices, sizeof(uint16_t), Primitives::star->GetIndexCount(), pointindexBuffer);
	}
}

void Engine::Renderer::DrawPrimitive(const Primitives::Primitive& primitive)
{
	instance->DrawPrimitiveImpl(primitive);
}

void Engine::Renderer::DrawTriangle()
{
	instance->DrawTriangleImpl();
}

void Engine::Renderer::SetInstance(Renderer* renderer)
{
	instance = renderer;
}

Engine::Renderer* Engine::Renderer::instance;

