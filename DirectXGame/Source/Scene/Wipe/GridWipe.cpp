#define NOMINMAX
#include "GridWipe.h"

#include "Core/Time.h"
#include "Math/Easing.h"

#include <2d/Sprite.h>
#include <algorithm>
#include <cmath>

using namespace KamataEngine;

GridWipe::GridWipe() = default;

GridWipe::~GridWipe() = default;

void GridWipe::Initialize(uint32_t texture_handle) {
	m_sprite.reset(Sprite::Create(texture_handle, Vector2{0.0f, 0.0f}));
	m_sprite->SetPosition(m_position);
	m_sprite->SetSize(m_size);
	m_sprite->SetAnchorPoint(m_anchor);
	m_sprite->SetColor(m_color);
}

void GridWipe::Start(WipeState state, float duration) {
	m_state = state;
	m_duration = duration;
	m_timer = 0.0f;
	m_is_finished = false;
}

void GridWipe::Update() {
	if (m_is_finished) {
		return;
	}

	m_timer += Time::GetInstance()->GetDeltaTime();
	const float t = std::min(m_timer / m_duration, 1.0f);

	const bool is_closing = (m_state == WipeState::STATE_FADE_IN);
	const Vector2 from = is_closing ? Vector2{0.0f, -720.0f} : m_position;
	const Vector2 to = is_closing ? m_position : Vector2{0.0f, -360.0f};

	m_sprite->SetPosition({640.0f, std::lerp(from.y, to.y, Easing::OutBounce(t))});

	if (m_timer >= m_duration) {
		m_is_finished = true;
	}
}

void GridWipe::Draw() {
	if (m_sprite) {
		m_sprite->Draw();
	}
}