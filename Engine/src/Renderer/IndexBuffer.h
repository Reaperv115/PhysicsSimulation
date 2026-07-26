#pragma once
#include <d3d11.h>
#include <wrl.h>
#include "../Graphics/GraphicsContext.h"


using namespace Microsoft::WRL;

namespace Engine
{
	class IndexBuffer
	{
	public:
		IndexBuffer() = default;
		IndexBuffer(void* data, UINT elementbytesize, UINT numelements);
		~IndexBuffer();

		void CreateBuffer(void* data, UINT elementbytesize, int numelements);
		void BindBuffer(DXGI_FORMAT format);

		inline UINT GetIndexCount() const { return indexcount; }
		inline ComPtr<ID3D11Buffer> GetBuffer() const { return buffer; }

	private:
		ComPtr<ID3D11Buffer> buffer;
		UINT indexcount = 0;
	};
}