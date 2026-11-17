#pragma once

#include <chrono>

/// <summary>
/// Δタイム管理クラス
/// </summary>
class Time {
public:
	//==================================================
	// public methods
	//==================================================

	static Time* GetInstance();

	// コピー・ムーブ禁止
	Time(const Time&) = delete;
	Time& operator=(const Time&) = delete;
	Time(Time&&) = delete;
	Time& operator=(Time&&) = delete;

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

	Time() = default;
	~Time() = default;

	//==================================================
	// private variables
	//==================================================

	float m_delta_time = 0.0f;
	std::chrono::high_resolution_clock::time_point m_prev_time;

	bool m_is_first_frame = true;

	float m_accumulator = 0.0f; // 蓄積器
	const float k_fixed_delta_time = 1.0f / 60.0f;
};
