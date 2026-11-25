#pragma once

#include <3d/WorldTransform.h>

namespace KamataEngine {
class Camera;
class Model;
} // namespace KamataEngine

struct OBB;

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

	OBB GetOBB() const;
	void OnCollision();

	void Spawn();
	void ApprochTarget(const KamataEngine::Vector3& target);

	//=========================================================
	// accessor
	//=========================================================

	bool IsAlive() const { return m_is_alive; }

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
	//ワールド変換データ
	KamataEngine::WorldTransform m_world_transform{};

	//生存フラグ
	bool m_is_alive = false;

	/*--- 当たり判定 ---*/

	float m_width = 2.0f;
	float m_height = 2.0f;
	float m_depth = 2.0f;

	/*--- 移動 ---*/

	KamataEngine::Vector3 m_velocity{};
	float m_approch_speed = 2.0f;

	/*--- 回転 ---*/

	float m_turn_speed = 2.0f;
};
