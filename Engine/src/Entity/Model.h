#pragma once
#include <string>
#include <vector>
#include "../Renderer/Primitives.h"
#include <d3d11.h>
#include <wrl.h>
#include "Graphics/GraphicsContext.h"
#include "../Renderer/VertexBuffer.h"
#include "../Renderer/IndexBuffer.h"
#include "../Shaders/VertexShader.h"
#include "../Shaders/PixelShader.h"
#include "../ConstantBuffer/ConstantBuffer.h"
#include "Entity.h"
#include "../Camera/Camera.h"

using namespace DirectX;
using namespace Microsoft::WRL;

namespace Engine
{
	class Model : public Entity
	{
	public:
		Model(const std::string& filepath, const XMMATRIX& worldmatrix);
		~Model();

		void OnInit() override;
		void OnUpdate(float dt) override;
		void OnRender() override;
		void DrawModel();

		const Primitives::Vertex* GetVertices() const;
		const uint16_t* GetIndices() const;
		uint32_t GetVertexCount() const;
		uint32_t GetIndexCount() const;
		XMFLOAT4X4& GetWorldMatrix();

		bool Load();
		bool ParseOBJ();
	private:
		std::string filepath;
		std::vector<Primitives::Vertex> vertices;
		std::vector<XMFLOAT4> rgba;
		std::vector<uint16_t> indices;
		Transform transform;
		XMFLOAT4X4 wvp;

		ConstantBuffer<XMFLOAT4X4> constantbuffer;

		VertexShader vertexshader;
		PixelShader pixelshader;

		VertexBuffer vertexbuffer;
		IndexBuffer indexbuffer;
	};
}