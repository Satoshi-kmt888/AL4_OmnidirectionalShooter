#include "Enemy.h"

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
	return OBB{
	    .center = m_world_transform.translation_,
	    .orientations = {m_world_transform.rotation_.x, m_world_transform.rotation_.y, m_world_transform.rotation_.z},
	    .size = m_world_transform.scale_,
	};
}

void Enemy::OnCollision() { m_is_alive = false; }

void Enemy::SetModel(KamataEngine::Model* model) {
	assert(model);
	m_model = model;
}
