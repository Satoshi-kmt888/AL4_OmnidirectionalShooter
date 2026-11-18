#include "Player.h"

#include "Core/Time.h"
#include "GameObject/Bullet/Bullet.h"
#include "Geometry/OBB.h"
#include "Input/InputAction.h"
#include "Math/MathUtility.h"

#include <3d/Model.h>
#include <cassert>
#include <imgui.h>
#include <numbers>

using namespace KamataEngine;
using namespace MathUtility;

Player::Player() = default;

Player::~Player() = default;

void Player::Initialize(const InputAction* input, const ModelGroup& model_group) {
	m_input = input;
	m_model_group = model_group;

	m_world_transform.Initialize();
	m_world_transform.translation_.y = m_height * 0.5f;

	/*--- 弾 ---*/

	Bullet::SetModel(m_model_group.bullet);
	for (auto& bullet : m_bullets) {
		bullet = std::make_unique<Bullet>();
		bullet->Initialize();
	}
}

void Player::Update() {
	if (!m_is_alive) {
		return;
	}

	Move();

	BulletShot();

	m_world_transform.translation_ += m_velocity * Time::GetInstance()->GetDeltaTime();
	UpdateWorldTransform(m_world_transform);
}

void Player::Draw(const Camera* camera) {
	if (!m_is_alive) {
		return;
	}

	m_model_group.player->Draw(m_world_transform, *camera);

	for (const auto& bullet : m_bullets) {
		if (bullet->IsAlive()) {
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

OBB Player::GetOBB() const {
	Vector3 axis_x = {m_world_transform.matWorld_.m[0][0], m_world_transform.matWorld_.m[0][1], m_world_transform.matWorld_.m[0][2]};
	Vector3 axis_y = {m_world_transform.matWorld_.m[1][0], m_world_transform.matWorld_.m[1][1], m_world_transform.matWorld_.m[1][2]};
	Vector3 axis_z = {m_world_transform.matWorld_.m[2][0], m_world_transform.matWorld_.m[2][1], m_world_transform.matWorld_.m[2][2]};

	return OBB{
	    .center = m_world_transform.translation_,
	    .orientations = {Normalize(axis_x), Normalize(axis_y), Normalize(axis_z)},
	    .size = {(m_width * 0.5f),  (m_height * 0.5f), (m_depth * 0.5f) },
	};
}

void Player::OnCollision() { m_is_alive = false; }

Bullet* Player::GetBullet(size_t index) {
	if (index < k_max_bullet) {
		return m_bullets[index].get();
	}

	return nullptr;
}

void Player::Move() {
	Vector2 axis = m_input->GetMoveAxis();
	m_velocity.x = axis.x * m_move_speed;
	m_velocity.z = axis.y * m_move_speed;

	if (axis != Vector2{0.0f, 0.0f}) {
		float target_angle = std::atan2(axis.x, axis.y);
		m_world_transform.rotation_.y = target_angle + std::numbers::pi_v<float>;
	}
}

void Player::BulletShot() {
	if (m_bullet_cool_timer > 0.0f) {
		m_bullet_cool_timer -= Time::GetInstance()->GetDeltaTime();
	}

	if (m_input->IsPress(Action::ACTION_ATTACK)) {
		if (m_bullet_cool_timer <= 0.0f) {
			for (const auto& bullet : m_bullets) {
				if (!bullet->IsAlive()) {
					m_bullet_cool_timer = m_bullet_shot_interval;

					// 正面を求める
					Vector3 forward = {m_world_transform.matWorld_.m[2][0], m_world_transform.matWorld_.m[2][1], m_world_transform.matWorld_.m[2][2]};
					forward = Normalize(forward);

					Vector3 bullet_velocity = -forward * m_bullet_speed;
					bullet->Fire(m_world_transform.translation_, bullet_velocity);

					break;
				}
			}
		}
	}

	for (const auto& bullet : m_bullets) {
		if (bullet->IsAlive()) {
			bullet->Update();
		}
	}
}
