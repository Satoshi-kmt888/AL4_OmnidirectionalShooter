#pragma once

#include <math/Vector3.h>

namespace KamataEngine {
class Camera;
class WorldTransform;
} // namespace KamataEngine

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

	void Reset();

	void SetTarget(const KamataEngine::WorldTransform* target) { m_target = target; }

private:
	//==================================================
	// private methods
	//==================================================

	//==================================================
	// private variables
	//==================================================

	KamataEngine::Camera* m_camera = nullptr;

	const KamataEngine::WorldTransform* m_target = nullptr;
	KamataEngine::Vector3 m_target_offset{};
};
