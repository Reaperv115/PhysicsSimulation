#include "epch.h"
#include "AppLayer.h"

Engine::AppLayer::AppLayer()
{

}

Engine::AppLayer::~AppLayer()
{

}

void Engine::AppLayer::OnAttach()
{
	level.OnInit();
}

void Engine::AppLayer::OnUpdate(float dt)
{
	level.OnUpdate(dt);
}

void Engine::AppLayer::OnRender()
{
	level.OnRender();
}
