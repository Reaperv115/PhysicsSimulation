#include "epch.h"
#include "Level.h"

App::Level::Level()
{
}

App::Level::~Level()
{

}

void App::Level::OnInit()
{
	Engine::ObjSystem::GetInstance()->Initialize();
}

void App::Level::OnUpdate(float dt)
{
	
	auto& camera = Engine::Renderer::GetInstance()->GetCamera();
	if (camera)
	{
		if (Engine::Input::IsKeyDown('W'))
		{
			camera->MoveForward();
		}
		if (Engine::Input::IsKeyDown('S'))
		{
			camera->MoveBackward();
		}
		if (Engine::Input::IsKeyDown('A'))
		{
			camera->MoveLeft();
		}
		if (Engine::Input::IsKeyDown('D'))
		{
			camera->MoveRight();
		}
		camera->OnUpdate(dt);
	}

	for (auto& obj : Engine::ObjSystem::GetInstance()->GetObjects())
	{
		obj->OnUpdate(dt);
	}

	if (Engine::ImGuiLayer::AddShape())
	{
		Engine::ObjSystem::GetInstance()->AddShape();
	}
}

void App::Level::OnRender()
{
	for (auto& obj : Engine::ObjSystem::GetInstance()->GetObjects())
	{
		Engine::Renderer::GetInstance()->DrawPrimitive(*obj);
	}

	for (auto& star : Primitives::stars)
	{
		Engine::Renderer::GetInstance()->DrawPrimitive(*star);
	}

}


