#pragma once
#include "Layer.h"

namespace Engine
{
	class LayerStack
	{
	public:
		LayerStack();
		~LayerStack();

		void PushLayer(std::unique_ptr<Layer> layer);
		void PushOverlay(std::unique_ptr<Layer> overlay);
		void PopLayer(Layer* layer);
		void PopOverlay(Layer* overlay);

		std::vector<std::unique_ptr<Layer>>::iterator iterator;
		std::vector<std::unique_ptr<Layer>>::iterator begin() { return layers.begin(); }
		std::vector<std::unique_ptr<Layer>>::iterator end() { return layers.end(); }
		std::vector<std::unique_ptr<Layer>>::reverse_iterator rbegin() { return layers.rbegin(); }
		std::vector<std::unique_ptr<Layer>>::reverse_iterator rend() { return layers.rend(); }
	private:
		std::vector<std::unique_ptr<Layer>> layers;
		unsigned int layerInsertIndex = 0;
	};
}