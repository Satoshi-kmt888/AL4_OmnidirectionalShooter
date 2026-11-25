#include "Enemy.h"

#include "Core/Random.h"
#include "Core/Time.h"
#include "Geometry/OBB.h"
#include "Math/MathUtility.h"

#include <3d/Model.h>
#include <cassert>
#include <cmath>
#include <numbers>

using namespace KamataEngine;
using namespace MathUtility;

Enemy::Enemy() = default;

Enemy::~Enemy() = default;

void Enemy::Initialize() {
	m_world_transform.Initialize();

	m_is_alive = true;
}

void Enemy::Update() {
	if (!m_is_alive) {
		return;
	}

	m_world_transform.translation_ += m_velocity * Time::GetInstance()->GetDeltaTime();
	UpdateWorldTransform(m_world_transform);
}

void Enemy::Draw(const Camera* camera) const {
	if (!m_is_alive) {
		return;
	}

	m_model->Draw(m_world_transform, *camera);
}

OBB Enemy::GetOBB() const {
	Vector3 axis_x = {m_world_transform.matWorld_.m[0][0], m_world_transform.matWorld_.m[0][1], m_world_transform.matWorld_.m[0][2]};
	Vector3 axis_y = {m_world_transform.matWorld_.m[1][0], m_world_transform.matWorld_.m[1][1], m_world_transform.matWorld_.m[1][2]};
	Vector3 axis_z = {m_world_transform.matWorld_.m[2][0], m_world_transform.matWorld_.m[2][1], m_world_transform.matWorld_.m[2][2]};

	return OBB{
	    .center = m_world_transform.translation_,
	    .orientations = {Normalize(axis_x), Normalize(axis_y), Normalize(axis_z)},
	    .size = {(m_width * 0.5f),  (m_height * 0.5f), (m_depth * 0.5f) },
	};
}

void Enemy::OnCollision() { m_is_alive = false; }

void Enemy::Spawn() {
	m_world_transform.translation_ = {Random::Range<float>(-50.0f, 50.0f), m_height, Random::Range<float>(-50.0f, 50.0f)};

	m_is_alive = true;
}

void Enemy::SetModel(KamataEngine::Model* model) {
	assert(model);
	m_model = model;
}

void Enemy::ApprochTarget(const KamataEngine::Vector3& target) {
	// 自分から接近対象への向きを計算する
	Vector3 dir_target = Normalize(target - m_world_transform.translation_);
	//向きと速さで速度を計算
	m_velocity = dir_target * m_approch_speed;

	//ベクトルの向きから回転の角度を求める
	float yaw = std::atan2(dir_target.x, dir_target.z);
	//最短回転角を計算する
	float diff = std::remainder(yaw - m_world_transform.rotation_.y, 2.0f * std::numbers::pi_v<float>);
	//フレームレート非依存の回転補間
	m_world_transform.rotation_.y += diff * (1.0f * std::exp(-m_turn_speed * Time::GetInstance()->GetDeltaTime()));
}
