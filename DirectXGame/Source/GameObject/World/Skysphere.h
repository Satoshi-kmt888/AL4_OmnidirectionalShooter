#pragma once

#include <3d/WorldTransform.h>

namespace KamataEngine {
class Camera;
class Model;
} // namespace KamataEngine

/// <summary>
/// 天球
/// </summary>
class Skysphere {
public:
	//==================================================
	// public methods
	//==================================================

	Skysphere();
	~Skysphere();

	void Initialize(KamataEngine::Model* model);
	void Update();
	void Draw(const KamataEngine::Camera* camera);

private:
	//==================================================
	// private methods
	//==================================================

	//==================================================
	// private variables
	//==================================================

	// エンジン所有クラスへの参照
	KamataEngine::Model* m_model = nullptr;

	KamataEngine::WorldTransform m_worldTransform{};
};
