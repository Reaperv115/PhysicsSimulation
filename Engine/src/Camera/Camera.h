#pragma once
#include <DirectXMath.h>
#include "Timer.h"
#include "Input/Input.h"
#include "../Entity/Entity.h"
#include "Core.h"

#pragma comment(lib, "d3d11.lib")

using namespace DirectX;

namespace Engine
{
	class Camera : public Entity
	{
	public:
		Camera(float fov = 90.0f, float  aspectratio = 16.0f / 9.0f);
		XMFLOAT4X4 GetMVP(XMMATRIX modelmatrix);

		static Camera* GetInstance()
		{
			return instance;
		}

		void OnInit() override;
		void OnUpdate(float dt);
		void OnRender() override;
		void UpdateTransform();

		void MoveForward();
		void MoveBackward();
		void MoveLeft();
		void MoveRight();
				
		void SetLookAtPosition(XMFLOAT3 lookatpos);
		void AdjustRotation(float yaw, float pitch, float roll);

		inline float GetAspectRatio() const { return f_aspectRatio; }

		static inline XMFLOAT4X4& GetViewMatrix() { return f4x4_viewMatrix; }
		static inline XMFLOAT4X4& GetProjectionMatrix() { return f4x4_projectionMatrix; }
		static XMFLOAT4X4 GetWorldViewProjection(const XMFLOAT4X4& worldmatrix);


	private:
		float f_nearZ;
		float f_farZ;
		float f_aspectRatio;
		float f_dx, f_dy;
		float f_yaw, f_pitch, f_roll;
		float f_speed = 5000.0f;
		float f_FoV;

		XMFLOAT3 f3_moveDirection = XMFLOAT3(0.0f, 0.0f, 1.0f);



		XMFLOAT4 f4_upDirection;
		static XMFLOAT4X4 f4x4_viewMatrix;
		static XMFLOAT4X4 f4x4_projectionMatrix;

		// Default "world" vectors
		XMFLOAT3 defaultForward = XMFLOAT3(0.0f, 0.0f, 1.0f);
		XMFLOAT3 defaultRight = XMFLOAT3(1.0f, 0.0f, 0.0f);
		XMFLOAT3 defaultUp = XMFLOAT3(0.0f, 1.0f, 0.0f);

		static Camera* instance;
	};
}

