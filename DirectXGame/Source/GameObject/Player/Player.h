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

struct OBB;
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

	// 当たり判定用
	OBB GetOBB() const;
	void OnCollision();

	//=========================================================
	// accessor
	//=========================================================

	const KamataEngine::WorldTransform& GetWorldTransform() const { return m_world_transform; }

	bool IsAlive() const { return m_is_alive; }

	size_t GetMaxBullet() const { return k_max_bullet; }
	Bullet* GetBullet(size_t index);

	//---------------------------------------------------------

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

	// モデル群
	ModelGroup m_model_group{};

	// ワールド変換データ
	KamataEngine::WorldTransform m_world_transform{};

	bool m_is_alive = true;

	/*--- 当たり判定 ---*/

	float m_width = 1.9f;
	float m_height = 2.0f;
	float m_depth = 1.9f;

	/*--- 移動 ---*/

	KamataEngine::Vector3 m_velocity{};
	float m_move_speed = 10.0f;

	/*--- 弾 ---*/

	static inline const uint32_t k_max_bullet = 32;
	std::array<std::unique_ptr<Bullet>, k_max_bullet> m_bullets;
	KamataEngine::Vector3 m_bullet_velocity = {0.0f, 0.0f, 24.0f};
	float m_bullet_shot_interval = 0.5f;
	float m_bullet_cool_timer = 0.0f;
};
