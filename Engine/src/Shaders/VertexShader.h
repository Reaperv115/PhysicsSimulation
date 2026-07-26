#pragma once
#include "Shader.h"
#include "../Graphics/GraphicsContext.h"
#include <string>
#include <iostream>
#include <d3dcompiler.h>

#pragma comment(lib, "d3dcompiler.lib")

namespace Engine
{
	class VertexShader : public Shader
	{
	public:
		VertexShader() = default;
		VertexShader(const std::string& filepath);
		virtual ~VertexShader() = default;
		virtual void CreateShader(const std::string& filepath) override;
		virtual void Bind() override;

		inline ComPtr<ID3D11VertexShader>& GetVertexShader() { return vertexshader; }
		inline ComPtr<ID3D11InputLayout>& GetInputLayout() { return inputlayOut; }
	private:
		ComPtr<ID3DBlob> errorBlob;
		ComPtr<ID3DBlob> vsblob;
		ComPtr<ID3D11InputLayout> inputlayOut;
		ComPtr<ID3D11VertexShader> vertexshader;
	};

}