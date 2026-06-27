#pragma once
#include <DirectXMath.h>
#include "Timer.h"
#include "Transform.h"
#include "Input/Input.h"

#pragma comment(lib, "d3d11.lib")

using namespace DirectX;

namespace Engine
{
	class Camera
	{
	public:
		Camera();
		Camera(float fov, float  aspectratio);
		XMFLOAT4X4 GetMVP(XMMATRIX modelmatrix);

		void OnInitialize(float fov, float aspectratio);
		void OnUpdate(float dt);
		void UpdateTransform();

		void MoveForward();
		void MoveBackward();
		void MoveLeft();
		void MoveRight();
		void SetLookAtPosition(XMFLOAT3 lookatpos);
		void AdjustRotation(float yaw, float pitch, float roll);

		inline float GetAspectRatio() const { return f_aspectRatio; }

	private:
		float nearZ;
		float farZ;
		float f_aspectRatio;
		float dx, dy;
		float yaw, pitch, roll;
		float speed = 5000.0f;

		Transform transform;
		XMFLOAT3 f3_moveDirection = XMFLOAT3(0.0f, 0.0f, 1.0f);


		XMFLOAT4 f4_upDirection;
		XMFLOAT4X4 f4x4_viewMatrix, f4x4_projectionMatrix;

		// Default "world" vectors
		XMFLOAT3 defaultForward = XMFLOAT3(0.0f, 0.0f, 1.0f);
		XMFLOAT3 defaultRight = XMFLOAT3(1.0f, 0.0f, 0.0f);
		XMFLOAT3 defaultUp = XMFLOAT3(0.0f, 1.0f, 0.0f);

		
	};
}

