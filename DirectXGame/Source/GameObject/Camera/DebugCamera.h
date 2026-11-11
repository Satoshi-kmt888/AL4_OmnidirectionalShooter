#pragma once

#include <3d/Camera.h>

namespace KamataEngine {
class Input;
}

/// <summary>
/// デバッグカメラ
/// /// </summary>
class DebugCamera {
public:
	//==================================================
	// publice methods
	//==================================================

	DebugCamera();
	~DebugCamera();

	void Initialize();
	void Update();

	const KamataEngine::Camera& GetCamera() const { return m_camera; }

private:
	//==================================================
	// private methods
	//==================================================

	/// <summary>
	/// 視点操作
	/// </summary>
	void Rotate();

	/// <summary>
	/// 移動
	/// </summary>
	void Move();

	//==================================================
	// private variables
	//==================================================

	// 別クラスへの参照ポインタ
	KamataEngine::Input* m_input = nullptr;

	// カメラ
	KamataEngine::Camera m_camera;

	// 操作性パラメータ
	float m_zoom_speed = 0.01f;
	float m_rotate_sensitivity = 0.002f;

	// 回転角度
	float m_yaw = 0.0f;
	float m_pitch = 0.0f;
};
