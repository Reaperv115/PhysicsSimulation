#pragma once
#include "Shader.h"
#include "../Graphics/GraphicsContext.h"
#include <string>
#include <iostream>
#include <d3dcompiler.h>

#pragma comment(lib, "d3dcompiler.lib")

namespace Engine
{
	class PixelShader : public Shader
	{
	public:
		PixelShader() = default;
		PixelShader(const std::string& filepath);
		virtual ~PixelShader() = default;
		virtual void CreateShader(const std::string& filepath) override;
		virtual void Bind() override;

		inline ComPtr<ID3D11PixelShader>& GetPixelShader() { return pixelshader; }
	private:
		ComPtr<ID3DBlob> errorBlob;
		ComPtr<ID3DBlob> psblob;
		ComPtr<ID3D11PixelShader> pixelshader;
	};

}