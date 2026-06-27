#include "epch.h"
#include "ObjSystem.h"

Engine::ObjSystem* Engine::ObjSystem::instance = nullptr;

void Engine::ObjSystem::Initialize()
{
	Primitives::CreateStarField();
	InitializeScene();

	//AddShape();
}

void Engine::ObjSystem::AddShape()
{
	auto triangle = CreateUnique<Primitives::Triangle>();
	Primitives::GeneratePosition(*triangle);
	objects.push_back(std::move(triangle));
}

void Engine::ObjSystem::InitializeScene()
{
	objects.push_back(CreateUnique<Primitives::Triangle>());
	objects.push_back(CreateUnique<Primitives::Square>());
	objects.push_back(CreateUnique<Primitives::Cube>());
}
