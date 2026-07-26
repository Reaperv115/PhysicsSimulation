#include "epch.h"
#include "IndexBuffer.h"

Engine::IndexBuffer::IndexBuffer(void* data, UINT elementbytesize, UINT numelements)
{
	CreateBuffer(data, elementbytesize, numelements);
}

Engine::IndexBuffer::~IndexBuffer()
{

}

void Engine::IndexBuffer::CreateBuffer(void* data, UINT elementbytesize, int numelements)
{
	D3D11_BUFFER_DESC bufferdesc = {};
	bufferdesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bufferdesc.ByteWidth = elementbytesize * numelements;
	bufferdesc.Usage = D3D11_USAGE_DYNAMIC;
	bufferdesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	bufferdesc.MiscFlags = 0;
	bufferdesc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA bufferdata = {};
	bufferdata.pSysMem = data;
	GraphicsContext::GetDevice()->CreateBuffer(&bufferdesc, data ? &bufferdata : nullptr, buffer.GetAddressOf());
}

void Engine::IndexBuffer::BindBuffer(DXGI_FORMAT format)
{
	GraphicsContext::GetDeviceContext()->IASetIndexBuffer(buffer.Get(), format, 0);
}
