#include "Bullet.h"

#include "Core/Time.h"
#include "Geometry/Sphere.h"
#include "Math/MathUtility.h"

#include <3d/Model.h>
#include <cassert>
#include <imgui.h>

using namespace KamataEngine;
using namespace MathUtility;

Bullet::Bullet() = default;

Bullet::~Bullet() = default;

void Bullet::Initialize() { m_world_transform.Initialize(); }

void Bullet::Update() {
	m_current_time += Time::GetInstance()->GetDeltaTime();
	if (m_current_time >= s_life_time) {
		m_current_time = 0.0f;
		m_is_shot = false;
	}

#ifdef DEVELOP
	// 開発中は弾の大きさを変えるためワールド変換データに適用する
	m_world_transform.scale_ = {s_scale, s_scale, s_scale};
#endif
	m_world_transform.translation_ += m_velocity * Time::GetInstance()->GetDeltaTime();
	WorldTransformUpdate(m_world_transform);
}

void Bullet::Draw(const Camera* camera) const { s_model->Draw(m_world_transform, *camera); }

Sphere Bullet::GetSphere() const { return Sphere{m_world_transform.translation_, s_scale}; }

void Bullet::SetModel(Model* model) { s_model = model; }

void Bullet::ControlImGui() {
#ifdef USE_IMGUI
	if (!ImGui::CollapsingHeader("Bullet")) {
		return;
	}

	ImGui::DragFloat("scale", &s_scale, 0.01f, 0.1f, 10.0f);
	ImGui::DragFloat("life time", &s_life_time, 0.1f, 0.1f, 10.0f);
#endif
}

void Bullet::Fire(const Vector3& position, const Vector3& velocity) {
	m_world_transform.translation_ = position;
	m_velocity = velocity;

	m_is_shot = true;

	// 即座にワールド変換データの更新を入れ、描画や判定ずれを防ぐ
	WorldTransformUpdate(m_world_transform);
}
