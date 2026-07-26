#pragma once
#include <d3d11.h>
#include <wrl.h>
#include "../Graphics/GraphicsContext.h"


using namespace Microsoft::WRL;

namespace Engine
{
	class VertexBuffer
	{
	public:
		VertexBuffer() = default;
		VertexBuffer(void* data, UINT elementbytesize, UINT numelements);
		~VertexBuffer();

		void CreateBuffer(void* data, UINT elementbytesize, int numelements);
		void BindBuffer(UINT stride, UINT offset);

		inline ComPtr<ID3D11Buffer> GetBuffer() const { return buffer; }
		inline UINT GetVertexCount() const { return vertexcount; }
	private:
		ComPtr<ID3D11Buffer> buffer;
		UINT vertexcount = 0;
	};
}