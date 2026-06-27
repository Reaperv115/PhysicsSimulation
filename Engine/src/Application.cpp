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

	renderer = CreateUnique<Renderer>(gfx);

	layerstack.PushLayer(CreateUnique<Engine::AppLayer>());
	layerstack.PushLayer(CreateUnique<Engine::ImGuiLayer>(window->GetWindowHandle(), 
		renderer->GetGraphics()->GetDevice(), renderer->GetGraphics()->GetDeviceContext()));
}

void Engine::Application::OnUpdate()
{
	renderer->GetGraphics()->PrepareScene();

	Timer timer;


	for (const auto& layer : layerstack)
	{
		timer.Tick();
		float dt = timer.DeltaTime();
		layer->OnUpdate(dt);
		layer->OnRender();
	}
	renderer->GetGraphics()->PresentScene();

	Input::OnUpdate();
	window->Update();
}

void Engine::Application::PushLayer(std::unique_ptr<Layer> layer)
{
	layerstack.PushLayer(std::move(layer));
}

