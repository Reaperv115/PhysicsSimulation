#include "epch.h"
#include "SkyBox.h"

Engine::SkyBox::SkyBox()
{
	
	verts[0] = Primitives::Vertex(-5.0f, 5.0f, -5.0f, 1.0f, 0.0f, 0.0f, 1.0f);
	verts[1] = Primitives::Vertex(5.0f, 5.0f, -5.0f, 1.0f, 0.0f, 0.0f, 1.0f);
	verts[2] = Primitives::Vertex(-5.0f, -5.0f, -5.0f, 1.0f, 0.0f, 0.0f, 1.0f);
	verts[3] = Primitives::Vertex(5.0f, -5.0f, -5.0f, 1.0f, 0.0f, 0.0f, 1.0f);

	verts[4] = Primitives::Vertex(5.0f, 5.0f, 5.0f, 0.0f, 1.0f, 0.0f, 1.0f);
	verts[5] = Primitives::Vertex(-5.0f, 5.0f, 5.0f, 0.0f, 1.0f, 0.0f, 1.0f);
	verts[6] = Primitives::Vertex(5.0f, -5.0f, 5.0f, 0.0f, 1.0f, 0.0f, 1.0f);
	verts[7] = Primitives::Vertex(-5.0f, -5.0f, 5.0f, 0.0f, 1.0f, 0.0f, 1.0f);

	verts[8] = Primitives::Vertex(-5.0f, 5.0f, 5.0f, 1.0f, 0.0f, 0.0f, 1.0f);
	verts[9] = Primitives::Vertex(-5.0f, 5.0f, -5.0f, 0.0f, 1.0f, 0.0f, 1.0f);
	verts[10] = Primitives::Vertex(-5.0f, -5.0f, 5.0f, 0.0f, 0.0f, 1.0f, 1.0f);
	verts[11] = Primitives::Vertex(-5.0f, -5.0f, -5.0f, 1.0f, 0.0f, 0.0f, 1.0f);

	verts[12] = Primitives::Vertex(5.0f, 5.0f, -5.0f, 1.0f, 1.0f, 0.0f, 1.0f);
	verts[13] = Primitives::Vertex(5.0f, 5.0f, 5.0f, 1.0f, 1.0f, 0.0f, 1.0f);
	verts[14] = Primitives::Vertex(5.0f, -5.0f, -5.0f, 1.0f, 1.0f, 0.0f, 1.0f);
	verts[15] = Primitives::Vertex(5.0f, -5.0f, 5.0f, 1.0f, 1.0f, 0.0f, 1.0f);

	verts[16] = Primitives::Vertex(-5.0f, 5.0f, 5.0f, 0.0f, 1.0f, 1.0f, 1.0f);
	verts[17] = Primitives::Vertex(5.0f, 5.0f, 5.0f, 0.0f, 1.0f, 1.0f, 1.0f);
	verts[18] = Primitives::Vertex(-5.0f, 5.0f, -5.0f, 0.0f, 1.0f, 1.0f, 1.0f);
	verts[19] = Primitives::Vertex(5.0f, 5.0f, -5.0f, 0.0f, 1.0f, 1.0f, 1.0f);

	verts[20] = Primitives::Vertex(-5.0f, -5.0f, -5.0f, 1.0f, 0.0f, 1.0f, 1.0f);
	verts[21] = Primitives::Vertex(5.0f, -5.0f, -5.0f, 1.0f, 0.0f, 1.0f, 1.0f);
	verts[22] = Primitives::Vertex(-5.0f, -5.0f, 5.0f, 1.0f, 0.0f, 1.0f, 1.0f);
	verts[23] = Primitives::Vertex(5.0f, -5.0f, 5.0f, 1.0f, 0.0f, 1.0f, 1.0f);
	constantBuffer.Create(GraphicsContext::GetDevice(), &worldmatrix);
	//vertexshader
}

Engine::SkyBox::~SkyBox()
{

}

void Engine::SkyBox::Init()
{

}

void Engine::SkyBox::Render()
{

}
