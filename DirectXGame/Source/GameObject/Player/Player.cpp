#include "Player.h"

#include "Core/Time.h"
#include "GameObject/Bullet/Bullet.h"
#include "Input/InputAction.h"
#include "Math/MathUtility.h"

#include <3d/Model.h>
#include <cassert>
#include <imgui.h>

using namespace KamataEngine;
using namespace MathUtility;

Player::Player() = default;

Player::~Player() = default;

void Player::Initialize(const InputAction* input, const ModelGroup& model_group) {
	m_input = input;
	m_model_group = model_group;

	m_world_transform.Initialize();

	/*--- 弾 ---*/

	Bullet::SetModel(m_model_group.bullet);
	for (auto& bullet : m_bullets) {
		bullet = std::make_unique<Bullet>();
		bullet->Initialize();
	}
}

void Player::Update() {
	Move();

	BulletShot();

	m_world_transform.translation_ += m_velocity * Time::GetInstance()->GetDeltaTime();
	WorldTransformUpdate(m_world_transform);
}

void Player::Draw(const Camera* camera) {
	m_model_group.player->Draw(m_world_transform, *camera);

	for (const auto& bullet : m_bullets) {
		if (bullet->IsShot()) {
			bullet->Draw(camera);
		}
	}
}

void Player::ControlImGui() {
#ifdef USE_IMGUI
	if (ImGui::CollapsingHeader("Player")) {
		ImGui::DragFloat("move_speed", &m_move_speed, 0.01f);
	}

	Bullet::ControlImGui();
#endif
}

void Player::Move() {
	m_velocity.x = m_input->GetMoveAxis().x * m_move_speed;
	m_velocity.z = m_input->GetMoveAxis().y * m_move_speed;
}

void Player::BulletShot() {
	if (m_bullet_cool_timer > 0.0f) {
		m_bullet_cool_timer -= Time::GetInstance()->GetDeltaTime();
	}

	if (m_input->IsPress(Action::ACTION_ATTACK)) {
		if (m_bullet_cool_timer <= 0.0f) {
			for (const auto& bullet : m_bullets) {
				if (!bullet->IsShot()) {
					m_bullet_cool_timer = m_bullet_shot_interval;
					bullet->Fire(m_world_transform.translation_, m_bullet_velocity);

					break;
				}
			}
		}
	}

	for (const auto& bullet : m_bullets) {
		if (bullet->IsShot()) {
			bullet->Update();
		}
	}
}
