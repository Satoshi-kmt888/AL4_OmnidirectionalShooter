#pragma once

#include <chrono>

/// <summary>
/// Δタイム管理クラス
/// </summary>
class Clock {
public:
	//==================================================
	// public methods
	//==================================================

	static Clock* GetInstance();

	// コピー・ムーブ禁止
	Clock(const Clock&) = delete;
	Clock& operator=(const Clock&) = delete;
	Clock(Clock&&) = delete;
	Clock& operator=(Clock&&) = delete;

	void Update();

	/// <summary>
	/// Δタイムの誤差修正
	/// </summary>
	/// <returns></returns>
	bool IsFixedUpdateRequired();

	//==================================================
	// accessor
	//==================================================

	float GetDeltaTime() const { return m_delta_time; }

private:
	//==================================================
	// private methods
	//==================================================

	Clock() = default;
	~Clock() = default;

	//==================================================
	// private variables
	//==================================================

	float m_delta_time = 0.0f;
	std::chrono::high_resolution_clock::time_point m_prev_time;

	bool m_is_first_frame = true;

	float m_accumulator = 0.0f; // 蓄積器
	const float k_fixed_delta_time = 1.0f / 60.0f;
};
