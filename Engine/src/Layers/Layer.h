#pragma once
#include "../Renderer/Renderer.h"

namespace Engine
{
	class Layer
	{
	public:
		Layer(){}
		virtual ~Layer(){}
		virtual void OnAttach(){}
		virtual void OnDetach(){}
		virtual void OnUpdate(float dt) {}
		virtual void OnRender() {}
	};
}