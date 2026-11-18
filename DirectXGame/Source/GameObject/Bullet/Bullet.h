#pragma once

#include <3d/WorldTransform.h>
#include <math/Vector3.h>

namespace KamataEngine {
class Camera;
class Model;
} // namespace KamataEngine

struct Sphere;

/// <summary>
///
/// </summary>
class Bullet {
public:
	//=========================================================
	// public methods
	//=========================================================

	Bullet();
	~Bullet();

	void Initialize();
	void Update();
	void Draw(const KamataEngine::Camera* camera) const;

	static void ControlImGui();

	void Fire(const KamataEngine::Vector3& position, const KamataEngine::Vector3& velocity);

	// 当たり判定用
	Sphere GetSphere() const;
	void OnCollision();

	//=========================================================
	// accessor
	//=========================================================

	bool IsAlive() const { return m_is_alive; }

	//---------------------------------------------------------

	static void SetModel(KamataEngine::Model* model);

	void SetIsAlive(bool is_alive) { m_is_alive = is_alive; }

private:
	//=========================================================
	// private methods
	//=========================================================

	//=========================================================
	// public variables
	//=========================================================

	// モデル(同じモデルを使う)
	static inline KamataEngine::Model* s_model = nullptr;
	KamataEngine::WorldTransform m_world_transform{};

	KamataEngine::Vector3 m_velocity{};

	static inline float s_scale = 0.5f;

	bool m_is_alive = false;
	static inline float s_life_time = 3.0f;
	float m_current_time = 0.0f;
};
