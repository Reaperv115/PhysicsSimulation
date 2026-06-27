#pragma once
#include <windows.h>
#include "vendor/imgui/imgui.h"
#include "vendor/imgui/imgui_impl_dx11.h"
#include "vendor/imgui/imgui_impl_win32.h"
#include "Layers/Layer.h"
#include <d3d11.h>
#include <wrl.h>
#include <print>
#include "Renderer/Renderer.h"

using namespace Microsoft::WRL;


namespace Engine
{
	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		ImGuiLayer(HWND hwnd, ComPtr<ID3D11Device> device, ComPtr<ID3D11DeviceContext> devicecontext);
		virtual ~ImGuiLayer();
		virtual void OnAttach()override;
		virtual void OnDetach() override;
		virtual void OnUpdate(float dt) override;
		virtual void OnRender() override;

		static inline bool AddShape() { return addShape; }
	private:
		HWND hwnd;
		ComPtr<ID3D11Device> device;
		ComPtr<ID3D11DeviceContext> devicecontext;
	private:
		static bool addShape;
	};
}