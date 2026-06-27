#include "epch.h"
#include "LayerStack.h"

Engine::LayerStack::LayerStack()
{
}

Engine::LayerStack::~LayerStack()
{

}

void Engine::LayerStack::PushLayer(std::unique_ptr<Layer> layer)
{
	layers.emplace(layers.begin() + layerInsertIndex, std::move(layer));
	layerInsertIndex++;
	layers[layerInsertIndex - 1]->OnAttach();
}

void Engine::LayerStack::PushOverlay(std::unique_ptr<Layer> overlay)
{
	layers.emplace(layers.begin() + layerInsertIndex, std::move(overlay));
	layerInsertIndex++;
	layers[layerInsertIndex - 1]->OnAttach();
}

void Engine::LayerStack::PopLayer(Layer* layer)
{
	auto it = std::find_if(layers.begin(), layers.end(), 
		[&](const std::unique_ptr<Layer>& p) { return p.get() == layer; });
	if (it != layers.end())
	{
		(*it)->OnDetach();
		layers.erase(it);
		layerInsertIndex--;
	}
}

void Engine::LayerStack::PopOverlay(Layer* overlay)
{
	PopLayer(overlay);
}
