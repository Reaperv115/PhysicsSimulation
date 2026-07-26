#pragma once
#include "Layers/Layer.h"
#include "Layers/LayerStack.h"
#include "../Levels/Level.h"
#include <d3d11.h>
#include <wrl.h>
#include "Renderer/Renderer.h"

using namespace DirectX;
using namespace Microsoft::WRL;

namespace Engine
{
	class AppLayer : public Engine::Layer
	{
	public:
		AppLayer();
		~AppLayer();

		void OnAttach() override;
		void OnUpdate(float dt) override;
		void OnRender() override;

	private:
		App::Level  level;
	};
}

