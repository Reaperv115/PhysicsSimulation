#pragma once
#include "AppWindow.h"
#include "Layers/LayerStack.h"
#include "Graphics/Graphics.h"
#include "Renderer/Renderer.h"
#include <string>
#include "Timer.h"
#include "AppLayers/AppLayer.h"
#include "AppLayers/ImGuiLayer.h"
#include "Core.h"
#include "ObjSystem/ObjSystem.h"


namespace Engine
{
	struct ApplicationSpecification
	{
		std::wstring name = L"Application";
		Engine::WindowProperties windowProperties;
	};
	class Application
	{
		
	public:
		Application(HINSTANCE inst, const ApplicationSpecification& appspec = ApplicationSpecification());
		~Application();

		inline bool IsRunning() { return isRunning; }
		inline Unique<AppWindow>& GetWindow() { return window; }

		void OnInitialize(HINSTANCE inst, const ApplicationSpecification& appspec);
		void OnUpdate();

		void PushLayer(Unique<Layer> layer);


	private:
		Unique<AppWindow> window;
		Unique<Graphics> gfx;
		Unique<Renderer> renderer;
		LayerStack layerstack;
		bool isRunning = true;
	};
}