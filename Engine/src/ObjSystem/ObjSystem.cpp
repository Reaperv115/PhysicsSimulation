#include "epch.h"
#include "ObjSystem.h"

Engine::ObjSystem* Engine::ObjSystem::instance = nullptr;

void Engine::ObjSystem::Initialize()
{
	//Primitives::CreateStarField();
	InitializeScene();

}

void Engine::ObjSystem::AddShape()
{
	auto triangle = CreateUnique<Primitives::Triangle>();
	Primitives::GeneratePosition(*triangle);
	objects.push_back(std::move(triangle));
}

void Engine::ObjSystem::InitializeScene()
{
	/*objects.push_back(CreateUnique<Primitives::Triangle>());
	objects.push_back(CreateUnique<Primitives::Square>());*/
	//objects.push_back(CreateUnique<Primitives::Cube>());

	auto adam = CreateUnique<Model>("src/Models/blender_adam.obj", XMMatrixTranslationFromVector(XMVectorSet(-1.0f, 0.0f, 0.0f, 1.0f)));
	adam->OnInit();
	models.push_back(std::move(adam));

	/*XMMATRIX scalematrix = XMMatrixScaling(-1.0f, 1.0f, 1.0f);
	XMMATRIX transmatrix = XMMatrixTranslationFromVector(XMVectorSet(1.0f, 0.0f, 0.0f, 1.0f));
	XMMATRIX combined = scalematrix * transmatrix;*/
	auto eve = CreateUnique<Model>("src/Models/blender_eve_rigged.obj", XMMatrixTranslationFromVector(XMVectorSet(1.0f, 0.0f, 0.0f, 1.0f)));
	eve->OnInit();
	models.push_back(std::move(eve));
}
