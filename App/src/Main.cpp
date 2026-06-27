// Engine.cpp : Defines the entry point for the application.
//
#include "epch.h"
#include "Application.h"




int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{

	Engine::ApplicationSpecification appSpec;
	appSpec.name = L"Application";
	appSpec.windowProperties.width = 1920;
	appSpec.windowProperties.height = 1080;


	auto app = Engine::CreateUnique<Engine::Application>(hInstance, appSpec);
	//app->PushLayer(Engine::CreateUnique<App::AppLayer>());

	while (app->GetWindow()->IsRunning())
	{
		app->OnUpdate();
	}


	return 0;
}