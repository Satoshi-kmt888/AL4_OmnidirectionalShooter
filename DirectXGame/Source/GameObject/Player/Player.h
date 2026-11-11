#pragma once

#include <3d/WorldTransform.h>
#include <math/Vector3.h>

namespace KamataEngine {
class Camera;
class Model;
} // namespace KamataEngine

class InputAction;

/// <summary>
/// プレイヤー
/// </summary>
class Player {
public:
	//=========================================================
	// public methods
	//=========================================================

	Player();
	~Player();

	void Initialize(const InputAction* input, KamataEngine::Model* model);
	void Update();
	void Draw(const KamataEngine::Camera* camera);

	//=========================================================
	// accessor
	//=========================================================

	const KamataEngine::WorldTransform& GetWorldTransform() const { return m_world_transform; }

private:
	//=========================================================
	// private methods
	//=========================================================

	void Move();

	//=========================================================
	// private variables
	//=========================================================

	// 入力
	const InputAction* m_input = nullptr;

	// モデル
	KamataEngine::Model* m_model = nullptr;
	// ワールド変換データ
	KamataEngine::WorldTransform m_world_transform{};

	KamataEngine::Vector3 m_velocity{};
};
