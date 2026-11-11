#pragma once

#include <math/Vector3.h>

namespace KamataEngine {
class Camera;
class WorldTransform;
} // namespace KamataEngine

/// <summary>
/// モード
/// </summary>
enum class Mode {
	MODE_FOLLOW,
};

/// <summary>
/// カメラコントローラー
/// </summary>
class CameraController {
public:
	//==================================================
	// public methods
	//==================================================

	CameraController();
	~CameraController();

	void Initialize(KamataEngine::Camera* camera);
	void Update();

	void ImGuiControl();

	void Reset();

	void SetTarget(const KamataEngine::WorldTransform* target) { m_target = target; }

private:
	//==================================================
	// private methods
	//==================================================

	//==================================================
	// private variables
	//==================================================

	//操作するカメラのポインタ
	KamataEngine::Camera* m_camera = nullptr;

	//追従対象のワールド変換データ
	const KamataEngine::WorldTransform* m_target = nullptr;
	KamataEngine::Vector3 m_target_offset{};

	float m_angle = 0.0f; //見下ろす角度(度)
};
