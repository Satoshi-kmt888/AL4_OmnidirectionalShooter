#include "CameraController.h"

#include "Math/MathUtility.h"

#include <3d/Camera.h>
#include <3d/WorldTransform.h>
#include <cassert>
#include <imgui.h>

using namespace KamataEngine;
using namespace MathUtility;

CameraController::CameraController() = default;

CameraController::~CameraController() = default;

void CameraController::Initialize(Camera* camera) {
	assert(camera);
	m_camera = camera;

	m_pitch = 32.0f;
	m_camera->rotation_.x = ConvertToRadian(m_pitch);

	m_target_offset = {0.0f, 20.0f, -32.0f};
}

void CameraController::Update() {
	switch (m_mode) {
		using enum Mode;
	case MODE_FOLLOW:
		UpdateFollow();
		break;
	default:
		break;
	}
}

void CameraController::ControlImGui() {
#ifdef USE_IMGUI
	if (!ImGui::CollapsingHeader("CameraController")) {
		return;
	}

	if (ImGui::TreeNode("common")) {
		ImGui::DragFloat3("translation", &m_camera->translation_.x, 0.1f);
		ImGui::DragFloat("pitch", &m_pitch, 0.1f);
		m_camera->rotation_.x = ConvertToRadian(m_pitch);
	}

	if (ImGui::TreeNode("follow")) {
		ImGui::DragFloat3("target offset", &m_target_offset.x, 0.01f);
		ImGui::DragFloat("follow delay", &m_follow_delay, 0.01f);
	}
#endif
}

void CameraController::Reset() { m_camera->translation_ = m_target_offset; }

void CameraController::UpdateFollow() {
	Vector3 ideal_position = m_target->translation_ + m_target_offset;
	m_camera->translation_ += (ideal_position - m_camera->translation_) * m_follow_delay;
}
