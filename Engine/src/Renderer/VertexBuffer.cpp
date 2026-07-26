#include "epch.h"
#include "VertexBuffer.h"

Engine::VertexBuffer::VertexBuffer(void* data, UINT elementbytesize, UINT numelements)
{
	CreateBuffer(data, elementbytesize, numelements);
}

Engine::VertexBuffer::~VertexBuffer()
{

}

void Engine::VertexBuffer::CreateBuffer(void* data, UINT elementbytesize, int numelements)
{
	D3D11_BUFFER_DESC bufferdesc = {};
	bufferdesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferdesc.ByteWidth = elementbytesize * numelements;
	bufferdesc.Usage = D3D11_USAGE_DYNAMIC;
	bufferdesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	D3D11_SUBRESOURCE_DATA bufferdata = {};
	bufferdata.pSysMem = data;
	GraphicsContext::GetDevice()->CreateBuffer(&bufferdesc, data ? &bufferdata : nullptr, buffer.GetAddressOf());

}

void Engine::VertexBuffer::BindBuffer(UINT stride, UINT offset)
{
	GraphicsContext::GetDeviceContext()->IASetVertexBuffers(0, 1, buffer.GetAddressOf(), &stride, &offset);
}
