#include "DebugCamera.h"

#include "Math/MathUtility.h"

#include <cmath>
#include <input/Input.h>

using namespace MathUtility;

DebugCamera::DebugCamera() = default;

DebugCamera::~DebugCamera() = default;

void DebugCamera::Initialize() {
	// 入力クラスのインスタンスを取得
	m_input = KamataEngine::Input::GetInstance();

	// カメラを初期化
	m_camera.Initialize();
}

void DebugCamera::Update() {
	//
	Rotate();
	Move();

	// カメラの行列更新処理
	m_camera.UpdateMatrix();
}

void DebugCamera::Rotate() {
	if (m_input->IsPressMouse(1)) {
		m_yaw += static_cast<float>(m_input->GetMouseMove().lX) * m_rotate_sensitivity;
		m_pitch += static_cast<float>(m_input->GetMouseMove().lY) * m_rotate_sensitivity;
	}

	m_camera.rotation_ = KamataEngine::Vector3{m_pitch, m_yaw, 0.0f};
}

void DebugCamera::Move() {
	if (!m_input->IsPressMouse(1)) {
		return;
	}

	// 現在向いている方向を求める
	auto forward = KamataEngine::Vector3{std::cos(m_pitch) * std::sin(m_yaw), -std::sin(m_pitch), std::cos(m_pitch) * std::cos(m_yaw)};
	KamataEngine::Vector3 worldUp = {0.0f, 1.0f, 0.0f};
	KamataEngine::Vector3 right = Cross(worldUp, forward);
	KamataEngine::Vector3 moveDir = {0.0f, 0.0f, 0.0f};

	forward = Normalize(forward);
	right = Normalize(right);
	float speed = 0.5f;
	if (m_input->PushKey(DIK_LSHIFT)) {
		speed = 1.0f;
	}

	// 前後移動
	if (m_input->PushKey(DIK_W)) {
		moveDir = moveDir + forward;
	}

	if (m_input->PushKey(DIK_S)) {
		moveDir = moveDir - forward;
	}

	// 左右移動
	if (m_input->PushKey(DIK_A)) {
		moveDir = moveDir - right;
	}

	if (m_input->PushKey(DIK_D)) {
		moveDir = moveDir + right;
	}

	// 上下移動
	if (m_input->PushKey(DIK_E)) {
		moveDir = moveDir + worldUp;
	}

	if (m_input->PushKey(DIK_Q)) {
		moveDir = moveDir - worldUp;
	}

	// 座標の更新
	if (Length(moveDir) > 0.0f) {
		m_camera.translation_ = m_camera.translation_ + speed * Normalize(moveDir);
	}
}
