#include "Player.h"

#include "Math/MathUtility.h"

#include <3d/Model.h>
#include <cassert>

using namespace KamataEngine;

Player::Player() = default;

Player::~Player() = default;

void Player::Initialize(Model* model) {
	assert(model);
	m_model = model;

	m_world_transform.Initialize();
}

void Player::Update() { MathUtility::WorldTransformUpdate(m_world_transform); }

void Player::Draw(const Camera* camera) {
	if (m_model) {
		m_model->Draw(m_world_transform, *camera);
	}
}
