#pragma once

#include "IWipe.h"

#include <cstdint>
#include <math/Vector2.h>
#include <math/Vector4.h>
#include <memory>

namespace KamataEngine {
class Sprite;
}

/// <summary>
/// グリッドワイプ
/// </summary>
class GridWipe : public IWipe {
public:
	//==================================================
	// publice methods
	//==================================================

	GridWipe();
	~GridWipe() override;

	void Initialize(uint32_t texture_handle);
	void Update() override;
	void Draw() override;

	void Start(WipeState state, float duration) override;

	bool IsFinished() const override { return m_is_finished; }

	//==================================================
	// accessor
	//==================================================

	WipeState GetState() const override { return m_state; }

private:
	//==================================================
	// private methods
	//==================================================

	//==================================================
	// private variables
	//==================================================

	// スタート時に初期化する項目
	WipeState m_state = WipeState::STATE_NONE;
	float m_duration = 0.0f; // 継続時間はシーン側が決める(こちらは受け取るだけ)
	float m_timer = 0.0f;
	bool m_is_finished = true;

	std::unique_ptr<KamataEngine::Sprite> m_sprite;
	KamataEngine::Vector2 m_anchor = {0.5f, 0.5f};
	KamataEngine::Vector2 m_position = {640.0f, 360.0f};
	KamataEngine::Vector2 m_size = {1280.0f, 720.0f};
	KamataEngine::Vector4 m_color = {0.0f, 0.0f, 0.0f, 1.0f};
};
