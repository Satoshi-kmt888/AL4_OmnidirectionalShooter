#pragma once

#include <3d/WorldTransform.h>

namespace KamataEngine {
class Camera;
class Model;
} // namespace KamataEngine

/// <summary>
/// 敵
/// </summary>
class Enemy {
public:
	//=========================================================
	// public methods
	//=========================================================

	Enemy();
	~Enemy();

	void Initialize();
	void Update();
	void Draw(const KamataEngine::Camera* camera) const;

	//=========================================================
	// accessor
	//=========================================================

	//---------------------------------------------------------

	static void SetModel(KamataEngine::Model* model);

private:
	//=========================================================
	// private methods
	//=========================================================

	//=========================================================
	// private variables
	//=========================================================

	// モデル(同じモデルを使う)
	static inline KamataEngine::Model* m_model = nullptr;

	KamataEngine::WorldTransform m_world_transform{};
};
