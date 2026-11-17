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

	void ControlImGui();

	void Reset();

	void SetTarget(const KamataEngine::WorldTransform* target) { m_target = target; }

private:
	//==================================================
	// private methods
	//==================================================

	void UpdateFollow();

	//==================================================
	// private variables
	//==================================================

	Mode m_mode = Mode::MODE_FOLLOW;

	// 操作するカメラのポインタ
	KamataEngine::Camera* m_camera = nullptr;

	float m_pitch = 0.0f; // 見下ろす角度(度)

	/*--- 追従 ---*/

	// 追従対象のワールド変換データ
	const KamataEngine::WorldTransform* m_target = nullptr;
	KamataEngine::Vector3 m_target_offset{};
	float m_follow_delay = 0.16f;
};
