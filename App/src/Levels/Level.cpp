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
	if (Engine::Input::IsKeyDown('W'))
	{
		Engine::Camera::GetInstance()->MoveForward();
		
	}
	if (Engine::Input::IsKeyDown('S'))
	{
		Engine::Camera::GetInstance()->MoveBackward();
	}
	if (Engine::Input::IsKeyDown('A'))
	{
		Engine::Camera::GetInstance()->MoveLeft();
	}
	if (Engine::Input::IsKeyDown('D'))
	{
		Engine::Camera::GetInstance()->MoveRight();
	}
	Engine::Camera::GetInstance()->OnUpdate(dt);

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
		Engine::Renderer::DrawPrimitive(*obj);
	}

	for (auto& star : Primitives::stars)
	{
		Engine::Renderer::DrawPrimitive(*star);
	}

	for (auto& model : Engine::ObjSystem::GetInstance()->GetModels())
	{
		model->OnRender();
	}
}


