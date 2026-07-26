#include "epch.h"
#include "Camera.h"



Engine::Camera::Camera(float fov /*= 90.0f*/, float aspectratio /*= 16.0f / 9.0f*/)
	: f_nearZ(0.1f), f_farZ(1000.0f), f_yaw(0.0f), f_pitch(0.0f), f_roll(0.0f),
	f_FoV(fov), f_aspectRatio(aspectratio), f_dx(0.0f), f_dy(0.0f)
{
	instance = this;
}

XMFLOAT4X4 Engine::Camera::GetMVP(XMMATRIX modelmatrix)
{
	XMMATRIX tmpview = XMLoadFloat4x4(&this->f4x4_viewMatrix);
	XMMATRIX tmpproj = XMLoadFloat4x4(&this->f4x4_projectionMatrix);

	XMMATRIX xmmvp = modelmatrix * tmpview * tmpproj;
	XMFLOAT4X4 mvp;
    XMStoreFloat4x4(&mvp, xmmvp);
    return mvp;
}

void Engine::Camera::OnInit()
{
	
	this->transform.f4_position = XMFLOAT4(0.0f, 0.0f, -3.0f, 0.0f);
	this->f3_moveDirection = XMFLOAT3(0.0f, 0.0f, 1.0f);
	this->f4_upDirection = XMFLOAT4(0.0f, 1.0f, 0.0f, 0.0f);

	XMVECTOR eyePos = XMLoadFloat4(&transform.f4_position);
	XMVECTOR focusPt = XMLoadFloat3(&f3_moveDirection);
	XMVECTOR upDir = XMLoadFloat4(&f4_upDirection);

	XMVECTOR cameraTarget = eyePos + focusPt;

	XMStoreFloat4x4(&this->f4x4_viewMatrix, XMMatrixLookAtLH(eyePos, cameraTarget, upDir));

	XMStoreFloat4x4(&this->f4x4_projectionMatrix, XMMatrixPerspectiveFovLH(this->f_FoV, this->f_aspectRatio, this->f_nearZ, this->f_farZ));
}

void Engine::Camera::OnUpdate(float dt)
{
	if (Input::IsMouseButtonDown(VK_RBUTTON))
	{
		this->f_dx = Input::GetMouseDeltaX();
		this->f_dy = Input::GetMouseDeltaY();

		this->transform.f3_rotation.x += this->f_dx * 0.005f;
		this->transform.f3_rotation.y -= this->f_dy * 0.005f;
		this->transform.f3_rotation.y = std::clamp(this->transform.f3_rotation.y, -XM_PIDIV2 + 0.01f, XM_PIDIV2 - 0.01f);

	}
	UpdateTransform();
}


void Engine::Camera::OnRender()
{

}

void Engine::Camera::UpdateTransform()
{
	
	XMVECTOR movedir = XMVectorSet(
		cosf(this->transform.f3_rotation.y) * sinf(this->transform.f3_rotation.x),
		sinf(this->transform.f3_rotation.y),
		cosf(this->transform.f3_rotation.y) * cosf(this->transform.f3_rotation.x),
		0.0f
	);
	movedir = XMVector3Normalize(movedir);

	XMVECTOR eyePos = XMLoadFloat4(&this->transform.f4_position);

	XMVECTOR target = eyePos + movedir;


	XMVECTOR upDir = XMLoadFloat3(&this->defaultUp);

	XMMATRIX viewmatrix = XMMatrixLookAtLH(eyePos, target, upDir);

	XMStoreFloat4x4(&f4x4_viewMatrix, viewmatrix);
	XMStoreFloat3(&f3_moveDirection, movedir);
}

void Engine::Camera::MoveForward()
{
	XMMATRIX rotationmatrix = XMMatrixRotationRollPitchYaw(this->f_pitch, this->f_yaw, this->f_roll);
	XMVECTOR direction = XMVector3Transform(XMLoadFloat3(&this->f3_moveDirection), rotationmatrix);
	XMVECTOR position = XMLoadFloat4(&this->transform.f4_position);
	position += direction * Timer::DeltaTime() * this->f_speed;
	XMStoreFloat4(&this->transform.f4_position, position);
}

void Engine::Camera::MoveBackward()
{
	XMMATRIX rotationmatrix = XMMatrixRotationRollPitchYaw(this->f_pitch, this->f_yaw, this->f_roll);
	XMVECTOR direction = XMVector3Transform(XMLoadFloat3(&this->f3_moveDirection), rotationmatrix);
	XMVECTOR position = XMLoadFloat4(&this->transform.f4_position);
	position -= direction * Timer::DeltaTime() * this->f_speed;
	XMStoreFloat4(&this->transform.f4_position, position);
}

void Engine::Camera::MoveRight()
{
	XMMATRIX rotationmatrix = XMMatrixRotationRollPitchYaw(this->f_pitch, this->f_yaw, this->f_roll);
	XMVECTOR relativeforward = XMVector3Transform(XMLoadFloat3(&this->f3_moveDirection), rotationmatrix);
	XMVECTOR up = XMLoadFloat3(&this->defaultUp);
	XMVECTOR relativeright = XMVector3Cross(relativeforward, up);
	XMVECTOR position = XMLoadFloat4(&this->transform.f4_position);
	position -= relativeright * Timer::DeltaTime() * this->f_speed;
	XMStoreFloat4(&this->transform.f4_position, position);
}

void Engine::Camera::MoveLeft()
{
	XMMATRIX rotationmatrix = XMMatrixRotationRollPitchYaw(this->f_pitch, this->f_yaw, this->f_roll);
	XMVECTOR relativeforward = XMVector3Transform(XMLoadFloat3(&this->f3_moveDirection), rotationmatrix);
	XMVECTOR up = XMLoadFloat3(&this->defaultUp);
	XMVECTOR relativeright = XMVector3Cross(relativeforward, up);
	XMVECTOR position = XMLoadFloat4(&this->transform.f4_position);
	position += relativeright * Timer::DeltaTime() * this->f_speed;
	XMStoreFloat4(&this->transform.f4_position, position);
}


void Engine::Camera::SetLookAtPosition(XMFLOAT3 lookatpos)
{
	lookatpos.x = this->transform.f4_position.x - lookatpos.x;
	lookatpos.y = this->transform.f4_position.y - lookatpos.y;
	lookatpos.z = this->transform.f4_position.z - lookatpos.z;

	f_pitch = 0.0f;
	if (lookatpos.y != 0.0f)
	{
		float distance = sqrt(lookatpos.x * lookatpos.x + lookatpos.z * lookatpos.z);
		f_pitch = atan(lookatpos.y / distance);
	}

	f_yaw = 0.0f;
	if (lookatpos.x != 0.0f)
	{
		f_yaw = atan(lookatpos.x / lookatpos.z);

	}

	AdjustRotation(XMConvertToRadians(f_yaw), XMConvertToRadians(f_pitch), 0.0f);
}

void Engine::Camera::AdjustRotation(float yaw, float pitch, float roll)
{
	this->transform.f3_rotation.x += yaw;
	this->transform.f3_rotation.y += pitch;
	this->transform.f3_rotation.z += roll;
	UpdateTransform();
}

XMFLOAT4X4 Engine::Camera::GetWorldViewProjection(const XMFLOAT4X4& worldmatrix)
{
	XMMATRIX world = XMLoadFloat4x4(&worldmatrix);
	XMMATRIX view = XMLoadFloat4x4(&f4x4_viewMatrix);
	XMMATRIX projection = XMLoadFloat4x4(&f4x4_projectionMatrix);
	XMMATRIX wvp = world * view * projection;
	XMFLOAT4X4 wvp_float;
	XMStoreFloat4x4(&wvp_float, wvp);
	return wvp_float;
}


XMFLOAT4X4 Engine::Camera::f4x4_viewMatrix;
XMFLOAT4X4 Engine::Camera::f4x4_projectionMatrix;
Engine::Camera* Engine::Camera::instance = nullptr;
