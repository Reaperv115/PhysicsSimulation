#pragma once
#include <wrl.h>
#include <d3d11.h>
#include <string>
#include <iostream>

using namespace Microsoft::WRL;

namespace Engine
{
	class Shader
	{
	protected:
		Shader() = default;
		virtual ~Shader() = default;
		virtual void CreateShader(const std::string& filepath) = 0;
		virtual void Bind() = 0;
		ComPtr<ID3D11InputLayout> inputLayout;
		ComPtr<ID3DBlob> shaderBlob;
	};
}