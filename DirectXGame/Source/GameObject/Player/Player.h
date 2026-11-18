#pragma once

#include <3d/WorldTransform.h>
#include <array>
#include <cstdint>
#include <math/Vector3.h>
#include <memory>

namespace KamataEngine {
class Camera;
class Model;
} // namespace KamataEngine

class InputAction;
class Bullet;

/// <summary>
/// プレイヤー
/// </summary>
class Player {
public:
	// モデル群
	struct ModelGroup {
		KamataEngine::Model* player = nullptr;
		KamataEngine::Model* bullet = nullptr;
	};

	//=========================================================
	// public methods
	//=========================================================

	Player();
	~Player();

	void Initialize(const InputAction* input, const ModelGroup& model_group);
	void Update();
	void Draw(const KamataEngine::Camera* camera);

	void ControlImGui();

	//=========================================================
	// accessor
	//=========================================================

	const KamataEngine::WorldTransform& GetWorldTransform() const { return m_world_transform; }

private:
	//=========================================================
	// private methods
	//=========================================================

	void Move();

	void BulletShot();

	//=========================================================
	// private variables
	//=========================================================

	// 入力
	const InputAction* m_input = nullptr;

	// モデル
	ModelGroup m_model_group{};

	// ワールド変換データ
	KamataEngine::WorldTransform m_world_transform{};

	/*--- 移動 ---*/

	KamataEngine::Vector3 m_velocity{};
	float m_move_speed = 16.0f;

	/*--- 弾 ---*/

	static inline const uint32_t k_max_bullet = 32;
	std::array<std::unique_ptr<Bullet>, k_max_bullet> m_bullets;
	KamataEngine::Vector3 m_bullet_velocity = {0.0f, 0.0f, 24.0f};
	float m_bullet_shot_interval = 0.5f;
	float m_bullet_cool_timer = 0.0f;
};
