#pragma once

#include <array>
#include <cstdint>
#include <math/Vector2.h>
#include <vector>
#include <Windows.h>
#include <Xinput.h>

namespace KamataEngine {
class Input;
}

/// <summary>
///
/// </summary>
enum class Action {
	ACTION_DECIDE, // 決定
	ACTION_CANCEL, // キャンセル

	COUNT,
};

/// <summary>
/// 入力デバイス
/// </summary>
enum class InputDevice {
	DEVICE_KEYBOARD,
	DEVICE_MOUSE,
	DEVICE_PAD,
};

struct InputBinding {
	InputDevice device;
	int32_t code;
};

/// <summary>
/// 入力による動作
/// </summary>
class InputAction {
public:
	//=========================================================
	// public methods
	//=========================================================

	InputAction();
	~InputAction();

	void Register();
	void Update();

	bool IsPress(Action action) const;
	bool IsTrigger(Action action) const;
	bool IsRelease(Action action) const;

	KamataEngine::Vector2 CalcMoveAxis(const KamataEngine::Input* input, const XINPUT_STATE* pad_state);

private:
	//=========================================================
	// private methods
	//=========================================================

	void AddBinding(Action action, const InputBinding& binding);

	//=========================================================
	// private variables
	//=========================================================

	static constexpr size_t k_action_count = static_cast<size_t>(Action::COUNT);

	std::array<bool, k_action_count> m_current_state{};
	std::array<bool, k_action_count> m_previous_state{};

	std::array<std::vector<InputBinding>, k_action_count> m_bindings;

	KamataEngine::Vector2 m_move_axis{};
};
