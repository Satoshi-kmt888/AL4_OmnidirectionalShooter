#include "Enemy.h"

#include "Math/MathUtility.h"

#include <3d/Model.h>
#include <cassert>

using namespace KamataEngine;
using namespace MathUtility;

Enemy::Enemy() = default;

Enemy::~Enemy() = default;

void Enemy::Initialize() { m_world_transform.Initialize(); }

void Enemy::Update() { UpdateWorldTransform(m_world_transform); }

void Enemy::Draw(const Camera* camera) const { m_model->Draw(m_world_transform, *camera); }

void Enemy::SetModel(KamataEngine::Model* model) {
	assert(model);
	m_model = model;
}
