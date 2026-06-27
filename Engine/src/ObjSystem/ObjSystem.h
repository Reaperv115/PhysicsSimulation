#pragma once
#include "Core.h"
#include "../Renderer/primitives.h"

namespace Engine
{
	class ObjSystem
	{
	public:

		static ObjSystem* GetInstance()
		{
			if (!instance)
			{
				instance = new ObjSystem();
			}
			return instance;
		}

		void Initialize();
		void AddShape();
		void InitializeScene();

		Deque<Unique<Primitives::Primitive>>& GetObjects() { return objects; };

	private:
		Deque<Unique<Primitives::Primitive>> objects;
	private:
		static ObjSystem* instance;

	};
}