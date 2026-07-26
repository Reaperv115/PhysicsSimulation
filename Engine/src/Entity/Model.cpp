#include "epch.h"
#include "Model.h"
#include <fstream>
#include <sstream>

Engine::Model::Model(const std::string& filepath)
	: filepath(filepath)
{

}

Engine::Model::~Model()
{

}

void Engine::Model::OnInit()
{
	if (Load())
	{
		std::println("Obj file loaded successfully");
	}
	else
	{
		std::println("Obj file did not load successfully");
		
	}

	constantbuffer.Create(GraphicsContext::GetDevice(), &wvp);

	vertexshader = VertexShader("src/Shaders/VertexShader.hlsl");
	pixelshader = PixelShader("src/Shaders/PixelShader.hlsl");

	vertexbuffer = VertexBuffer(vertices.data(), sizeof(Primitives::Vertex), vertices.size());
	indexbuffer = IndexBuffer(indices.data(), sizeof(uint16_t), indices.size());


	XMStoreFloat4x4(&transform.worldmatrix, XMMatrixTranslationFromVector(XMVectorSet(0.0f, 2.0f, 0.0f, 1.0f)));
}

void Engine::Model::OnUpdate(float dt)
{

}

void Engine::Model::OnRender()
{
	DrawModel();
}

void Engine::Model::DrawModel()
{
	
	wvp = Camera::GetWorldViewProjection(transform.worldmatrix);

	GraphicsContext::GetDeviceContext()->IASetInputLayout(vertexshader.GetInputLayout().Get());
	GraphicsContext::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	constantbuffer.Update(GraphicsContext::GetDeviceContext(), &wvp);
	constantbuffer.BindVS(GraphicsContext::GetDeviceContext());

	UINT stride = sizeof(Primitives::Vertex);
	UINT offset = 0;
	vertexbuffer.BindBuffer(stride, offset);
	indexbuffer.BindBuffer(DXGI_FORMAT_R16_UINT);
	vertexshader.Bind();
	pixelshader.Bind();
	GraphicsContext::GetDeviceContext()->DrawIndexed(indices.size(), 0, 0);
}

const Primitives::Vertex* Engine::Model::GetVertices() const
{
	return vertices.empty() ? nullptr : vertices.data();
}

const uint16_t* Engine::Model::GetIndices() const
{
	return indices.empty() ? nullptr : indices.data();
}

uint32_t Engine::Model::GetVertexCount() const
{
	return vertices.size();
}

uint32_t Engine::Model::GetIndexCount() const
{
	return indices.size();
}

XMFLOAT4X4& Engine::Model::GetWorldMatrix()
{
	return transform.worldmatrix;
}

bool Engine::Model::Load()
{
	return ParseOBJ();
}

bool Engine::Model::ParseOBJ()
{
	std::ifstream file(filepath);
	if (!file.is_open())
		return false;
	
	std::vector<XMFLOAT3> positions;
	std::string line;

	while (std::getline(file, line))
	{
		std::istringstream iss(line);
		std::string type;
		iss >> type;

		if (type == "v")
		{
			float x, y, z;
			iss >> x >> y >> z;
			positions.push_back({ x, y, z });
		}
		else if (type == "f")
		{
			uint16_t v1, v2, v3;
			iss >> v1 >> v2 >> v3;

			indices.push_back(v1 - 1);
			indices.push_back(v2 - 1);
			indices.push_back(v3 - 1);
		}
	}

	// converting positions to vertices
	for (const auto& pos : positions)
	{
		vertices.push_back(Primitives::Vertex(pos.x, pos.y, pos.z, 1.0f, 1.0f, 1.0f, 1.0f));
	}

	file.close();
	return !vertices.empty();
}
