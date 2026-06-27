#pragma once
#include "Camera/Camera.h"
#include "Input/Input.h"
#include <print>
#include "Renderer/Renderer.h"
#include <vector>
#include "Core.h"
#include "../AppLayers/ImGuiLayer.h"
#include "ObjSystem/ObjSystem.h"

namespace App
{
	class Level
	{
	public:
		Level();
		~Level();

		void OnInit();
		void OnUpdate(float dt);
		void OnRender();

	private:
		/*Engine::Deque<Engine::Unique<Primitives::Primitive>> objects;
		Engine::Deque<Engine::Unique<Primitives::Dot>> stars;*/

	};
}