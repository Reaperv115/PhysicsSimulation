#pragma once
#include "epch.h"
#include <d3d11.h>
#include <wrl.h>
#include <DirectXMath.h>

#pragma comment(lib, "d3d11.lib")

using namespace Microsoft::WRL;
using namespace DirectX;

namespace Engine
{
	template<typename T>
	class ConstantBuffer
	{
	public:
		ConstantBuffer() = default;

		ConstantBuffer(ComPtr<ID3D11Device> device, const T* initialData = nullptr)
		{
			Create(device, initialData);
		}
		~ConstantBuffer() = default;

		void Create(ComPtr<ID3D11Device> device, const T* initialdata = nullptr)
		{
			D3D11_BUFFER_DESC bufferDesc = {};
			bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
			bufferDesc.ByteWidth = static_cast<UINT>(((sizeof(T) + 15) / 16) * 16);
			bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
			bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
			D3D11_SUBRESOURCE_DATA bufferData = {};
			bufferData.pSysMem = initialdata;
			HRESULT hr = device->CreateBuffer(&bufferDesc, &bufferData, buffer.GetAddressOf());
			if (FAILED(hr))
			{
				throw std::runtime_error("Failed to create constant buffer.");
			}
		}

		void Update(ComPtr<ID3D11DeviceContext> devicecontext, const T* data)
		{
			D3D11_MAPPED_SUBRESOURCE mappedResource = {};
			HRESULT hr = devicecontext->Map(buffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
			if (FAILED(hr))
			{
				throw std::runtime_error("Failed to map constant buffer.");
			}
			memcpy(mappedResource.pData, data, sizeof(T));
			devicecontext->Unmap(buffer.Get(), 0);
		}

		void BindVS(ComPtr<ID3D11DeviceContext> devicecontext, UINT startslot = 0)
		{
			if (!devicecontext || !buffer)
			{
				throw std::runtime_error("Device context or buffer is null in BindVS.");
			}
			devicecontext->VSSetConstantBuffers(startslot, 1, buffer.GetAddressOf());
		}

		void BindPS(ComPtr<ID3D11DeviceContext> devicecontext, UINT startslot = 0)
		{
			if (!devicecontext || !buffer)
			{
				throw std::runtime_error("Device context or buffer is null in BindPS.");
			}
			devicecontext->PSSetConstantBuffers(startslot, 1, buffer.GetAddressOf());
		}

		ComPtr<ID3D11Buffer> GetBuffer() const { return buffer;}

	private:
		ComPtr<ID3D11Buffer> buffer;
	};

}