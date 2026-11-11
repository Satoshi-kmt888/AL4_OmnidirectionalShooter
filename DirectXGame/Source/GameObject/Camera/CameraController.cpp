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

	m_angle = 32.0f;
	m_camera->rotation_.x = ConvertToRadian(m_angle);
	m_camera->translation_.y = 20.0f;
	m_camera->translation_.z = -32.0f;
}

void CameraController::Update() {
	//m_camera->translation_ = m_target_offset;
}

void CameraController::ImGuiControl() {
#ifdef USE_IMGUI
	if (ImGui::CollapsingHeader("CameraController")) {
		ImGui::DragFloat3("translation", &m_camera->translation_.x, 0.1f);
		ImGui::DragFloat("angle", &m_angle, 0.1f);
		m_camera->rotation_.x = ConvertToRadian(m_angle);
	}
#endif
}

void CameraController::Reset() { m_camera->translation_ = m_target_offset; }
