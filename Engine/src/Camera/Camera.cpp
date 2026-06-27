#include "epch.h"
#include "Camera.h"

Engine::Camera::Camera(float fov, float  aspectratio)
	: nearZ(0.1f), farZ(1000.0f), yaw(0.0f), pitch(0.0f), roll(0.0f)
{
	OnInitialize(fov, aspectratio);
}

Engine::Camera::Camera()
{

}

XMFLOAT4X4 Engine::Camera::GetMVP(XMMATRIX modelmatrix)
{
	XMMATRIX tmpview = XMLoadFloat4x4(&f4x4_viewMatrix);
	XMMATRIX tmpproj = XMLoadFloat4x4(&f4x4_projectionMatrix);

	XMMATRIX xmmvp = modelmatrix * tmpview * tmpproj;
	XMFLOAT4X4 mvp;
    XMStoreFloat4x4(&mvp, xmmvp);
    return mvp;
}

void Engine::Camera::OnInitialize(float fov, float aspectratio)
{
	f_aspectRatio = aspectratio;
	transform.f4_position = XMFLOAT4(0.0f, 0.0f, -3.0f, 0.0f);
	f3_moveDirection = XMFLOAT3(0.0f, 0.0f, 1.0f);
	f4_upDirection = XMFLOAT4(0.0f, 1.0f, 0.0f, 0.0f);

	XMVECTOR eyePos = XMLoadFloat4(&transform.f4_position);
	XMVECTOR focusPt = XMLoadFloat3(&f3_moveDirection);
	XMVECTOR upDir = XMLoadFloat4(&f4_upDirection);

	XMVECTOR cameraTarget = eyePos + focusPt;

	XMStoreFloat4x4(&f4x4_viewMatrix, XMMatrixLookAtLH(eyePos, cameraTarget, upDir));

	XMStoreFloat4x4(&f4x4_projectionMatrix, XMMatrixPerspectiveFovLH(fov, aspectratio, nearZ, farZ));
}

void Engine::Camera::OnUpdate(float dt)
{
	if (Input::IsMouseButtonDown(VK_RBUTTON))
	{
		dx = Input::GetMouseDeltaX();
		dy = Input::GetMouseDeltaY();

		transform.f3_rotation.x += dx * 0.005f;
		transform.f3_rotation.y -= dy * 0.005f;
		transform.f3_rotation.y = std::clamp(transform.f3_rotation.y, -XM_PIDIV2 + 0.01f, XM_PIDIV2 - 0.01f);

	}
	UpdateTransform();
}


void Engine::Camera::UpdateTransform()
{
	
	XMVECTOR movedir = XMVectorSet(
		cosf(transform.f3_rotation.y) * sinf(transform.f3_rotation.x),
		sinf(transform.f3_rotation.y),
		cosf(transform.f3_rotation.y) * cosf(transform.f3_rotation.x),
		0.0f
	);
	movedir = XMVector3Normalize(movedir);

	XMVECTOR eyePos = XMLoadFloat4(&transform.f4_position);

	XMVECTOR target = eyePos + movedir;


	XMVECTOR upDir = XMLoadFloat3(&defaultUp);

	XMMATRIX viewmatrix = XMMatrixLookAtLH(eyePos, target, upDir);

	XMStoreFloat4x4(&f4x4_viewMatrix, viewmatrix);
	XMStoreFloat3(&f3_moveDirection, movedir);
}

void Engine::Camera::MoveForward()
{
	XMMATRIX rotationmatrix = XMMatrixRotationRollPitchYaw(pitch, yaw, roll);
	XMVECTOR direction = XMVector3Transform(XMLoadFloat3(&f3_moveDirection), rotationmatrix);
	XMVECTOR position = XMLoadFloat4(&transform.f4_position);
	position += direction * Timer::DeltaTime() * speed;
	XMStoreFloat4(&transform.f4_position, position);
}

void Engine::Camera::MoveBackward()
{
	XMMATRIX rotationmatrix = XMMatrixRotationRollPitchYaw(pitch, yaw, roll);
	XMVECTOR direction = XMVector3Transform(XMLoadFloat3(&f3_moveDirection), rotationmatrix);
	XMVECTOR position = XMLoadFloat4(&transform.f4_position);
	position -= direction * Timer::DeltaTime() * speed;
	XMStoreFloat4(&transform.f4_position, position);
}

void Engine::Camera::MoveRight()
{
	XMMATRIX rotationmatrix = XMMatrixRotationRollPitchYaw(pitch, yaw, roll);
	XMVECTOR relativeforward = XMVector3Transform(XMLoadFloat3(&f3_moveDirection), rotationmatrix);
	XMVECTOR up = XMLoadFloat3(&defaultUp);
	XMVECTOR relativeright = XMVector3Cross(relativeforward, up);
	XMVECTOR position = XMLoadFloat4(&transform.f4_position);
	position -= relativeright * Timer::DeltaTime() * speed;
	XMStoreFloat4(&transform.f4_position, position);
}

void Engine::Camera::MoveLeft()
{
	XMMATRIX rotationmatrix = XMMatrixRotationRollPitchYaw(pitch, yaw, roll);
	XMVECTOR relativeforward = XMVector3Transform(XMLoadFloat3(&f3_moveDirection), rotationmatrix);
	XMVECTOR up = XMLoadFloat3(&defaultUp);
	XMVECTOR relativeright = XMVector3Cross(relativeforward, up);
	XMVECTOR position = XMLoadFloat4(&transform.f4_position);
	position += relativeright * Timer::DeltaTime() * speed;
	XMStoreFloat4(&transform.f4_position, position);
}

void Engine::Camera::SetLookAtPosition(XMFLOAT3 lookatpos)
{
	lookatpos.x = transform.f4_position.x - lookatpos.x;
	lookatpos.y = transform.f4_position.y - lookatpos.y;
	lookatpos.z = transform.f4_position.z - lookatpos.z;

	pitch = 0.0f;
	if (lookatpos.y != 0.0f)
	{
		float distance = sqrt(lookatpos.x * lookatpos.x + lookatpos.z * lookatpos.z);
		pitch = atan(lookatpos.y / distance);
	}

	yaw = 0.0f;
	if (lookatpos.x != 0.0f)
	{
		yaw = atan(lookatpos.x / lookatpos.z);

	}

	AdjustRotation(XMConvertToRadians(yaw), XMConvertToRadians(pitch), 0.0f);
}

void Engine::Camera::AdjustRotation(float yaw, float pitch, float roll)
{
	transform.f3_rotation.x += yaw;
	transform.f3_rotation.y += pitch;
	transform.f3_rotation.z += roll;
	UpdateTransform();
}
