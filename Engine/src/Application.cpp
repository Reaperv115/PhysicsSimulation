#include "epch.h"
#include "Application.h"


Engine::Application::Application(HINSTANCE inst, const ApplicationSpecification& appspec)
{
	OnInitialize(inst, appspec);
}

Engine::Application::~Application()
{

}

void Engine::Application::OnInitialize(HINSTANCE inst, const ApplicationSpecification& appspec)
{

	// creating window
	window = CreateUnique<AppWindow>(inst, appspec.windowProperties);
	window->Create();

	if (!window->GetWindowHandle())
	{
		throw std::runtime_error("Window handle is null");
	}
	Input::Initialize(window->GetWindowHandle());

	gfx = CreateUnique<Graphics>();
	gfx->InitGraphics(window->GetWindowHandle(), appspec.windowProperties.width, appspec.windowProperties.height);

	camera = CreateShared<Camera>();
	camera->OnInit();
	renderer = CreateUnique<Renderer>();
	renderer->OnInit();

	layerstack.PushLayer(CreateUnique<Engine::AppLayer>());
	layerstack.PushLayer(CreateUnique<Engine::ImGuiLayer>(window->GetWindowHandle(), 
		GraphicsContext::GetDevice(), GraphicsContext::GetDeviceContext()));
}

void Engine::Application::OnUpdate()
{
	gfx->PrepareScene();

	Timer timer;


	for (const auto& layer : layerstack)
	{
		timer.Tick();
		float dt = timer.DeltaTime();
		layer->OnUpdate(dt);
		layer->OnRender();
	}
	gfx->PresentScene();

	Input::OnUpdate();
	window->Update();
}

void Engine::Application::PushLayer(std::unique_ptr<Layer> layer)
{
	layerstack.PushLayer(std::move(layer));
}

