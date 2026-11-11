#include "Skysphere.h"

#include "Math/MathUtility.h"

#include <3d/Camera.h>
#include <3d/Model.h>
#include <cassert>

using namespace KamataEngine;

Skysphere::Skysphere() = default;

Skysphere::~Skysphere() = default;

void Skysphere::Initialize(Model* model) {
	assert(model);

	m_model = model;

	m_worldTransform.Initialize();
}

void Skysphere::Update() { MathUtility::WorldTransformUpdate(m_worldTransform); }

void Skysphere::Draw(const Camera* camera) { m_model->Draw(m_worldTransform, *camera); }
