#pragma once
#include <DirectXMath.h>
using namespace DirectX;

// yaw is x
// pitch is y
// roll is z

namespace Engine
{
	struct Transform
	{
		Transform() : f4_position(1.0f, 0.0f, 0.0f, 1.0f),
			f3_rotation(0.0f, 0.0f, 0.0f),
			f_scalar(1.0f) {}

		XMMATRIX worldmatrix;
		XMFLOAT4 f4_position;
		XMFLOAT3 f3_rotation;
		float f_scalar;
	};
}