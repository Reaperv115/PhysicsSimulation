#include "epch.h"
#include "PixelShader.h"

Engine::PixelShader::PixelShader(const std::string& filepath)
{
	CreateShader(filepath);
}

void Engine::PixelShader::CreateShader(const std::string& filepath)
{
	std::wstring wfilepath(filepath.begin(), filepath.end());

	HRESULT hr = D3DCompileFromFile(wfilepath.c_str(), nullptr, nullptr, "main", "ps_5_0", 0, 0, &psblob, nullptr);
	if (hr != S_OK)
		throw std::runtime_error("Failed to compile pixel shader");

	hr = GraphicsContext::GetDevice()->CreatePixelShader(psblob->GetBufferPointer(), psblob->GetBufferSize(), nullptr, &pixelshader);
	if (hr != S_OK)
	{
		throw std::runtime_error("Failed to create pixel shader");
	}
}

void Engine::PixelShader::Bind()
{
	GraphicsContext::GetDeviceContext()->PSSetShader(pixelshader.Get(), nullptr, 0);
}
