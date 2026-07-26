#pragma once
#include "Core.h"
#include "../Renderer/primitives.h"
#include "../Entity/Model.h"

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
		Deque<Unique<Model>>& GetModels() { return models; }

	private:
		Deque<Unique<Primitives::Primitive>> objects;
		Deque<Unique<Model>> models;
	private:
		static ObjSystem* instance;

	};
}