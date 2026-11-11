#include "Clock.h"

Clock* Clock::GetInstance() {
	static Clock instance;
	return &instance;
}

void Clock::Update() {
	// 現在の時間を取得する
	auto current_time = std::chrono::high_resolution_clock::now();
	// 1フレーム目だけは別の処理
	if (m_is_first_frame) {
		m_prev_time = current_time;
		m_delta_time = 0.0f;
		m_is_first_frame = false;
		return;
	}

	// 現在フレームと1フレーム前からΔタイムを求める
	std::chrono::duration<float> elapsed = current_time - m_prev_time;
	m_delta_time = elapsed.count();

	// 次の計算用に前フレームの時間を更新する
	m_prev_time = current_time;

	// Δタイムを蓄積する
	m_accumulator += m_delta_time;
}

bool Clock::IsFixedUpdateRequired() {
	// 蓄積器にたまった時間が溢れたら
	if (m_accumulator >= k_fixed_delta_time) {
		// 蓄積器を空にする
		m_accumulator -= k_fixed_delta_time;
		return true;
	}

	return false;
}
