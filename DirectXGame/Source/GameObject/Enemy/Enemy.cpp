#include "Enemy.h"

#include "Core/Random.h"
#include "Geometry/OBB.h"
#include "Math/MathUtility.h"

#include <3d/Model.h>
#include <cassert>

using namespace KamataEngine;
using namespace MathUtility;

Enemy::Enemy() = default;

Enemy::~Enemy() = default;

void Enemy::Initialize() {
	m_world_transform.Initialize();
	m_world_transform.translation_ = {0.0f, 0.0f, 10.0f};

	m_is_alive = true;
}

void Enemy::Update() {
	if (!m_is_alive) {
		return;
	}

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
	    .size = m_world_transform.scale_ * 0.5f,
	};
}

void Enemy::OnCollision() { m_is_alive = false; }

void Enemy::Spawn() {
	m_world_transform.translation_ = {Random::Range<float>(-10.0f, 10.0f), 0.0f, Random::Range<float>(-10.0f, 10.0f)};

	m_is_alive = true;
}

void Enemy::SetModel(KamataEngine::Model* model) {
	assert(model);
	m_model = model;
}
