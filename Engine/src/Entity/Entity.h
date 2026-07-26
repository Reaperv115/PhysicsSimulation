#pragma once
#include "Transform.h"

namespace Engine
{
	class Entity
	{
	protected:
		virtual void OnInit() = 0;
		virtual void OnUpdate(float dt) = 0;
		virtual void OnRender() = 0;


		Transform transform;
	};
}