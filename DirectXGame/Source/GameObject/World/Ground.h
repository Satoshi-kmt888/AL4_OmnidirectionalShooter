#pragma once

#include <3d/WorldTransform.h>

namespace KamataEngine {
class Camera;
class Model;
} // namespace KamataEngine

/// <summary>
/// 地面
/// </summary>
class Ground {
public:
	//==================================================
	// public methods
	//==================================================

	Ground();
	~Ground();

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

	// モデル
	KamataEngine::Model* m_model = nullptr;
	// ワールド変換データ
	KamataEngine::WorldTransform m_world_transform{};
};
