#include "Ground.h"

#include "Math/MathUtility.h"

#include <3d/Model.h>
#include <cassert>

using namespace KamataEngine;

Ground::Ground() = default;

Ground::~Ground() = default;

void Ground::Initialize(Model* model) {
	//
	assert(model);
	m_model = model;

	m_world_transform.Initialize();
}

void Ground::Update() { MathUtility::WorldTransformUpdate(m_world_transform); }

void Ground::Draw(const Camera* camera) { m_model->Draw(m_world_transform, *camera); }
