#include "ImGuiLayer.h"

Engine::ImGuiLayer::ImGuiLayer(HWND hwnd, 
	ComPtr<ID3D11Device> device, 
	ComPtr<ID3D11DeviceContext> devicecontext)
	: hwnd(hwnd), device(device), devicecontext(devicecontext)
{

}


Engine::ImGuiLayer::ImGuiLayer()
	: hwnd(nullptr), device(nullptr), devicecontext(nullptr)
{

}

Engine::ImGuiLayer::~ImGuiLayer()
{

}

void Engine::ImGuiLayer::OnAttach()
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	ImGui_ImplWin32_Init(static_cast<void*>(hwnd));
	ImGui_ImplDX11_Init(device.Get(), devicecontext.Get());
}

void Engine::ImGuiLayer::OnDetach()
{

}

void Engine::ImGuiLayer::OnUpdate(float dt)
{
	if (addShape)
	{
		std::println("Add Shape button clicked");
		addShape = false;
	}
}

void Engine::ImGuiLayer::OnRender()
{
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();

	ImGui::NewFrame();

	ImGui::SetNextWindowPos(ImVec2(1815, 0), ImGuiCond_Always);
	ImGui::Begin("Controls", nullptr, ImGuiWindowFlags_NoTitleBar
		| ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize
		| ImGuiWindowFlags_NoBackground);
	if (ImGui::Button("Add Shape"))
	{
		addShape = true;
	}
	ImGui::End();

	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

bool Engine::ImGuiLayer::addShape = false;
