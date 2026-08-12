#pragma once
#include <DirectXMath.h>
using namespace DirectX;


namespace Engine
{
	struct Transform
	{
		Transform() : f4_position(0.0f, 0.0f, 0.0f, 1.0f),
			f3_rotation(0.0f, 0.0f, 0.0f),
			f_scalar(1.0f) 
		{
			XMStoreFloat4x4(&worldmatrix, XMMatrixIdentity());
		}
		Transform(const XMMATRIX& matrix)
			: f4_position(0.0f, 0.0f, 0.0f, 1.0f),
			f3_rotation(0.0f, 0.0f, 0.0f),
			f_scalar(1.0f)
		{
			XMStoreFloat4x4(&worldmatrix, matrix);
		}

		XMFLOAT4X4 worldmatrix;
		XMFLOAT4 f4_position;
		XMFLOAT3 f3_rotation;
		float f_scalar;

		
	};
}