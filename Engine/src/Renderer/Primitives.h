#pragma once
#include <DirectXMath.h>
#include <d3d11.h>
#include <d3dcompiler.h>
#include "Core.h"
#include "Transform.h"
#include <deque>
#include <memory>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")

using namespace DirectX;


namespace Primitives
{
	enum class PrimitiveType
	{
		Dot = 0,
		Triangle,
		Square,
		Cube
	};
	struct Vertex
	{
		float x, y, z;      // Position
		float r, g, b, a;   // Color

		Vertex()
		{

		}

		Vertex(float x, float y, float z)
			: x(x), y(y), z(z)
		{
		}
		Vertex(float x, float y, float z, float r, float g, float b, float a)
			: x(x), y(y), z(z), r(r), g(g), b(b), a(a)
		{
		}
	};

	struct Primitive
	{
		float speed = 0.0f;
		XMVECTOR position = XMVectorZero();
		XMFLOAT3 rotation = {0.0f, 0.0f, 0.0f};
		XMMATRIX worldmatrix = XMMatrixIdentity();
		Engine::Transform transform;
		PrimitiveType type;

		virtual const Vertex* GetVertices() const = 0;
		virtual const uint16_t* GetIndices() const = 0;
		virtual const PrimitiveType GetType() const = 0;
		virtual const XMMATRIX GetWorldMatrix() const = 0;
		virtual uint32_t GetVertexCount() const = 0;
		virtual uint32_t GetIndexCount() const = 0;

		virtual void OnUpdate(float dt) = 0;

		virtual void SetPosition(float x, float y, float z) = 0;

		virtual ~Primitive() = default;
	};

	struct Dot : public Primitive
	{
		Vertex verts[1] = {
			Vertex(0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f)

		};
		Engine::Transform transform;
		Dot(float x, float y, float z)
		{
			// working on star field
			verts[0].x = x;
			verts[0].y = y;
			verts[0].z = z;
			transform.worldmatrix = XMMatrixIdentity();
			transform.worldmatrix *= XMMatrixTranslation(verts[0].x, verts[0].y, verts[0].z);
		}
		Dot()
		{
			verts[0].x = 0.0f;
			verts[0].y = 0.0f;
			verts[0].z = 0.0f;
			transform.worldmatrix = XMMatrixIdentity();
			transform.worldmatrix *= XMMatrixTranslation(verts[0].x, verts[0].y, verts[0].z);
		}
		uint16_t indices[1] = { 0 };
		virtual const Vertex* GetVertices() const override { return verts; }
		virtual const uint16_t* GetIndices() const override { return indices; }
		virtual const PrimitiveType GetType() const override { return PrimitiveType::Dot; }
		virtual const XMMATRIX GetWorldMatrix() const override { return transform.worldmatrix; }
		virtual uint32_t GetVertexCount() const override { return 1; }
		virtual uint32_t GetIndexCount() const override { return 1; }
		virtual void OnUpdate(float dt) override 
		{
			// stars do nothing right now
		}
		virtual void SetPosition(float x, float y, float z) override
		{
			transform.f4_position = { x, y, z, 1.0f };
			XMVECTOR tmp = XMLoadFloat4(&transform.f4_position);
			transform.worldmatrix = XMMatrixIdentity() * XMMatrixTranslationFromVector(tmp);
		}
		
	};
	

	struct Triangle : public Primitive
	{
		Vertex verts[3];
		Engine::Transform transform;

		Triangle()
		{
			verts[0] = Vertex(-0.5, -0.5, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f);
			verts[1] = Vertex(0.0, 0.5, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f);
			verts[2] = Vertex(0.5, -0.5, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f);
			transform.f4_position = { 0.0f, 0.0f, 0.0f, 1.0f };
			transform.worldmatrix = XMMatrixIdentity();
			speed = 5000.0f;
		}

		uint16_t indices[3] = {0, 1, 2};

		virtual const Vertex* GetVertices() const override { return verts; }
		virtual const uint16_t* GetIndices() const override { return indices; }
		virtual uint32_t GetVertexCount() const override { return 3; }
		virtual uint32_t GetIndexCount() const override { return 3; }
		virtual const XMMATRIX GetWorldMatrix() const override { return transform.worldmatrix; }
		virtual const PrimitiveType GetType() const override { return PrimitiveType::Triangle; }

		virtual void OnUpdate(float dt) override
		{
			rotation.y += dt * speed;
			XMVECTOR tmp = XMVectorSet(transform.f4_position.x, transform.f4_position.y, transform.f4_position.z, transform.f4_position.w);
			XMStoreFloat4(&transform.f4_position, tmp);
			transform.worldmatrix = XMMatrixRotationRollPitchYaw(rotation.x, rotation.y, rotation.z)
								  * XMMatrixTranslationFromVector(tmp);
			//transform.worldmatrix = XMMatrixInverse(nullptr, transform.worldmatrix);
		}

		virtual void SetPosition(float x, float y, float z) override
		{
			transform.f4_position = { x, y, z, 1.0f };
			XMVECTOR tmp = XMLoadFloat4(&transform.f4_position);
			transform.worldmatrix = XMMatrixIdentity() * XMMatrixTranslationFromVector(tmp);
		}
	};

	struct Square : public Primitive
	{
		Vertex verts[4];
		Engine::Transform transform;
		XMVECTOR center = XMVectorSet(1.0f, 0.0f, 0.0f, 1.0f);
		float orbitradius = 1.0f;
		float orbitspeed = 5000.0f;

		Square()
		{
			verts[0] = Vertex(-0.5f, 0.5f, 0.0f,	1.0f, 0.0f, 0.0f, 1.0f);
			verts[1] = Vertex(0.5f, 0.5f, 0.0f,	0.0f, 1.0f, 0.0f, 1.0f);
			verts[2] = Vertex(-0.5f, -0.5f, 0.0f,	0.0f, 0.0f, 1.0f, 1.0f);
			verts[3] = Vertex(0.5f, -0.5f, 0.0f,	0.0f, 0.0f, 1.0f, 1.0f);
			transform.f4_position = { 1.0f, 0.0f, 0.0f, 1.0f };
			transform.worldmatrix = XMMatrixIdentity();
			speed = 10000.0f;
		}
		uint16_t indices[6] =
						{ 0, 1, 2,
						2, 1, 3};

		virtual const Vertex* GetVertices() const override { return verts; }
		virtual const uint16_t* GetIndices() const override { return indices; }
		virtual uint32_t GetVertexCount() const override { return 4; }
		virtual uint32_t GetIndexCount() const override { return 6; }
		virtual const XMMATRIX GetWorldMatrix() const override { return transform.worldmatrix; }
		virtual const PrimitiveType GetType() const override { return PrimitiveType::Square; }

		virtual void OnUpdate(float dt) override
		{
			static float angle = 0.0f;
			angle += orbitspeed * dt;

			XMVECTOR orbitoffset = XMVectorSet(
				0.0f,
				orbitradius * cos(angle),
				orbitradius * sin(angle),
				1.0f
			);

			XMVECTOR newpos = center + orbitoffset;
			
			transform.worldmatrix = XMMatrixTranslationFromVector(newpos);
		}
		virtual void SetPosition(float x, float y, float z) override
		{
			transform.f4_position = { x, y, z, 1.0f };
			XMVECTOR tmp = XMLoadFloat4(&transform.f4_position);
			transform.worldmatrix = XMMatrixIdentity() * XMMatrixTranslationFromVector(tmp);
		}

	}; 

	struct Cube : public Primitive
	{
		Vertex vertices[24];
		uint16_t indices[36] =
		{
			0, 1, 2, 2, 1, 3,       // Front face
			4, 5, 6, 6, 5, 7,       // Back face
			8, 9, 10, 10, 9, 11,    // Left face
			12, 13, 14, 14, 13, 15, // Right face
			16, 17, 18, 18, 17, 19, // Top face
			20, 21, 22, 22, 21, 23  // Bottom face
		};
		Cube()
		{
			// Front face(z = -0.5) - Red
			vertices[0] = Vertex(-0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f);
			vertices[1] = Vertex(0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f);
			vertices[2] = Vertex(-0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f);
			vertices[3] = Vertex(0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f);

			// Back face (z = +0.5) - Green
			vertices[4] = Vertex(0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f);
			vertices[5] = Vertex(-0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f);
			vertices[6] = Vertex(0.5f, -0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f);
			vertices[7] = Vertex(-0.5f, -0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f);

			// Left face (x = -0.5) - Blue
			vertices[8] = Vertex(-0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f);
			vertices[9] = Vertex(-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f);
			vertices[10] = Vertex(-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f);
			vertices[11] = Vertex(-0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f);

			// Right face (x = +0.5) - Yellow
			vertices[12] = Vertex(0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 0.0f, 1.0f);
			vertices[13] = Vertex(0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 0.0f, 1.0f);
			vertices[14] = Vertex(0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 0.0f, 1.0f);
			vertices[15] = Vertex(0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 0.0f, 1.0f);

			// Top face (y = +0.5) - Cyan
			vertices[16] = Vertex(-0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 1.0f);
			vertices[17] = Vertex(0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 1.0f);
			vertices[18] = Vertex(-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f);
			vertices[19] = Vertex(0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f);

			// Bottom face (y = -0.5) - Magenta
			vertices[20] = Vertex(-0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 1.0f, 1.0f);
			vertices[21] = Vertex(0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 1.0f, 1.0f);
			vertices[22] = Vertex(-0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 1.0f, 1.0f);
			vertices[23] = Vertex(0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 1.0f, 1.0f);
			position = XMVectorSet(0.0f, 0.0f, 1.0f, 1.0f);
			worldmatrix = XMMatrixIdentity();
			speed = 15000.0f;
		}
		Engine::Transform transform;

		virtual const XMMATRIX GetWorldMatrix() const override { return transform.worldmatrix; }

		virtual const Vertex* GetVertices() const override { return vertices; }
		virtual const uint16_t* GetIndices() const override { return indices; }
		virtual uint32_t GetVertexCount() const override { return 24; }
		virtual uint32_t GetIndexCount() const override { return 36; }
		virtual const PrimitiveType GetType() const override { return PrimitiveType::Cube; }

		virtual void OnUpdate(float dt) override
		{
			rotation.y += dt * speed;
			XMVECTOR tmp;
			tmp = XMLoadFloat4(&transform.f4_position);
			transform.worldmatrix = XMMatrixInverse(nullptr, transform.worldmatrix);
			transform.worldmatrix = XMMatrixTranslationFromVector(tmp) * 
									XMMatrixRotationRollPitchYaw(rotation.x, rotation.y, rotation.z);
		}
		virtual void SetPosition(float x, float y, float z) override
		{
			transform.f4_position = { x, y, z, 1.0f };
			XMVECTOR tmp = XMLoadFloat4(&transform.f4_position);
			transform.worldmatrix = XMMatrixIdentity() * XMMatrixTranslationFromVector(tmp);
		}
	}; 

	inline Engine::Unique<Dot> star = nullptr;
	inline Engine::Unique<Triangle> triangle = nullptr;
	inline Engine::Unique<Square> square = nullptr;
	inline Engine::Unique<Cube> cube = nullptr;

	inline Engine::Deque<Engine::Unique<Dot>> stars;

	// This generates values from 0 to 20, divides by 100 to get 0.0 to 20.0, 
	// then subtracts 10.0 to shift the range to - 10.0 to 10.0.
	// Adjust the 2000 and 10.0f to control the distribution size.

	// Range - 5 to 5: Use rand() % 1000 and subtract 5.0f
	// Range - 50 to 50 : Use rand() % 10000 and subtract 50.0f
	inline void CreateStarField()
	{
		for (int i = 0; i < 1500; ++i)
		{
			float x = (static_cast<float>(rand() % 1000) / 100.0f) - 5.0f;
			float y = (static_cast<float>(rand() % 1000) / 100.0f) - 5.0f;
			float z = (static_cast<float>(rand() % 1000) / 100.0f) - 5.0f;
			stars.push_back(Engine::CreateUnique<Dot>(x, y, z));
		}
	}

	inline void GeneratePosition(Primitives::Primitive& prim)
	{
		float x = (static_cast<float>(rand() % 1000) / 100.0f) - 5.0f;
		float y = (static_cast<float>(rand() % 1000) / 100.0f) - 5.0f;
		float z = (static_cast<float>(rand() % 1000) / 100.0f) - 5.0f;

		//Primitives::triangle = Engine::CreateUnique<Primitives::Triangle>();
		prim.SetPosition(x, y, z);
	}
}