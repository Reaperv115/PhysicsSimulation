#include "epch.h"
#include "VertexShader.h"

Engine::VertexShader::VertexShader(const std::string& filepath)
{
	CreateShader(filepath);
}

void Engine::VertexShader::CreateShader(const std::string& filepath)
{
	HRESULT hr;
	std::wstring wfilepath(filepath.begin(), filepath.end());

	// creating input-layout
	D3D11_INPUT_ELEMENT_DESC inputlayout[] =
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};

	UINT vscompilerFlags = D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
	hr = D3DCompileFromFile(wfilepath.c_str(), nullptr, nullptr, "main", "vs_5_0", vscompilerFlags, 0, vsblob.GetAddressOf(), &errorBlob);
	if (FAILED(hr))
	{
		if (errorBlob)
		{
			std::string msg(static_cast<const char*>(errorBlob->GetBufferPointer()), errorBlob->GetBufferSize());
			std::cout << "Vertex shader compile error: " + msg + "\n";
		}
		else
		{
			char buf[512];
			FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, nullptr, hr, 0, buf, (DWORD)std::size(buf), nullptr);
			std::cout << "D3DCompileFromFile failed: " << std::string(buf) << std::endl;
		}
		throw std::runtime_error("Failed to compile vertex shader");
	}
	hr = GraphicsContext::GetDevice()->CreateInputLayout(inputlayout, 2, vsblob->GetBufferPointer(), vsblob->GetBufferSize(), inputlayOut.GetAddressOf());
	if (FAILED(hr))
	{
		throw std::runtime_error("Failed to create input layout");
	}
	
	hr = GraphicsContext::GetDevice()->CreateVertexShader(vsblob->GetBufferPointer(), vsblob->GetBufferSize(), nullptr, vertexshader.GetAddressOf());
	if (hr != S_OK)
	{
		throw std::runtime_error("Failed to create vertex shader");
	}
} 

void Engine::VertexShader::Bind()
{
	GraphicsContext::GetDeviceContext()->VSSetShader(vertexshader.Get(), nullptr, 0);
}
