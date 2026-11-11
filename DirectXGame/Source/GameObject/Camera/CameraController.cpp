#include "CameraController.h"

#include "Math/MathUtility.h"

#include <3d/Camera.h>
#include <3d/WorldTransform.h>
#include <cassert>

using namespace KamataEngine;
using namespace MathUtility;

CameraController::CameraController() = default;

CameraController::~CameraController() = default;

void CameraController::Initialize(Camera* camera) {
	assert(camera);
	m_camera = camera;
}

void CameraController::Update() { m_camera->translation_ = m_target_offset; }

void CameraController::Reset() { m_camera->translation_ = m_target_offset; }
