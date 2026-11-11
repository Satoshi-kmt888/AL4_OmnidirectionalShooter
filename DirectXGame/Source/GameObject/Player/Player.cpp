#include "Player.h"

#include "Core/Clock.h"
#include "Input/InputAction.h"
#include "Math/MathUtility.h"

#include <3d/Model.h>
#include <cassert>
#include <imgui.h>

using namespace KamataEngine;
using namespace MathUtility;

Player::Player() = default;

Player::~Player() = default;

void Player::Initialize(const InputAction* input, Model* model) {
	assert(model);

	m_input = input;
	m_model = model;

	m_world_transform.Initialize();
}

void Player::Update() {
	Move();

	m_world_transform.translation_ += m_velocity * Clock::GetInstance()->GetDeltaTime();
	WorldTransformUpdate(m_world_transform);
}

void Player::Draw(const Camera* camera) {
	if (m_model) {
		m_model->Draw(m_world_transform, *camera);
	}
}

void Player::ImGuiControl() {
#ifdef USE_IMGUI
	if (ImGui::CollapsingHeader("Player")) {
		ImGui::DragFloat("move_speed", &m_move_speed, 0.01f);
	}
#endif
}

void Player::Move() {
	m_velocity.x = m_input->GetMoveAxis().x * m_move_speed;
	m_velocity.z = m_input->GetMoveAxis().y * m_move_speed;
}
