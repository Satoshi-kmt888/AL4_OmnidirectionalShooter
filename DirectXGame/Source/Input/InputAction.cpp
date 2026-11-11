#define NOMINMAX
#include "InputAction.h"

#include <algorithm>
#include <cmath>
#include <input/Input.h>

using namespace KamataEngine;

namespace {
constexpr float k_stick_max = 32767.0f;
constexpr float k_stick_dead_zone = 0.24f;

size_t ToIndex(Action action) { return static_cast<size_t>(action); }

bool IsBindingPress(const InputBinding& binding, const Input* input, const XINPUT_STATE* pad_state) {
	switch (binding.device) {
		using enum InputDevice;
	case DEVICE_KEYBOARD:
		return input->PushKey(static_cast<BYTE>(binding.code));
	case DEVICE_MOUSE:
		return input->IsPressMouse(static_cast<BYTE>(binding.code));
	case DEVICE_PAD:
		return pad_state != nullptr && (pad_state->Gamepad.wButtons & binding.code) != 0;
	}

	return false;
}
} // namespace

InputAction::InputAction() = default;

InputAction::~InputAction() = default;

void InputAction::Register() {
	// 決定
	AddBinding(Action::ACTION_DECIDE, {InputDevice::DEVICE_KEYBOARD, DIK_SPACE});
	AddBinding(Action::ACTION_DECIDE, {InputDevice::DEVICE_PAD, XINPUT_GAMEPAD_A});
}

void InputAction::Update() {
	//
	m_previous_state = m_current_state;

	auto input = Input::GetInstance();

	XINPUT_STATE pad_state{};
	const bool has_pad = input->GetJoystickState(0, pad_state);
	const XINPUT_STATE* pad_state_ptr = has_pad ? &pad_state : nullptr;

	for (size_t i = 0; i < k_action_count; ++i) {
		bool is_press = false;

		for (const InputBinding& binding : m_bindings[i]) {
			if (IsBindingPress(binding, input, pad_state_ptr)) {
				is_press = true;
				break;
			}
		}

		m_current_state[i] = is_press;
	}
}

bool InputAction::IsPress(Action action) const { return m_current_state[ToIndex(action)]; }

bool InputAction::IsTrigger(Action action) const {
	const size_t index = ToIndex(action);
	return m_current_state[index] && !m_previous_state[index];
}

bool InputAction::IsRelease(Action action) const {
	const size_t index = ToIndex(action);
	return !m_current_state[index] && m_previous_state[index];
}

Vector2 InputAction::CalcMoveAxis(const Input* input, const XINPUT_STATE* pad_state) {
	Vector2 axis = {0.0f, 0.0f};

	/*--- 左スティック ---*/

	if (pad_state != nullptr) {
		const float x = static_cast<float>(pad_state->Gamepad.sThumbLX) / k_stick_max;
		const float y = static_cast<float>(pad_state->Gamepad.sThumbLY) / k_stick_max;
		const float length = std::sqrt(x * x + y * y);

		if (length > k_stick_dead_zone) {
			const float scaled = (std::min(length, 1.0f) - k_stick_dead_zone) / (1.0f - k_stick_dead_zone);
			axis.x = x / length * scaled;
			axis.y = y / length * scaled;
		}
	}

	/*--- キーボード ---*/

	if (axis.x == 0.0f && axis.y == 0.0f) {
		if (input->PushKey(DIK_A)) {
			axis.x -= 1.0f;
		}
		if (input->PushKey(DIK_D)) {
			axis.x += 1.0f;
		}
		if (input->PushKey(DIK_W)) {
			axis.y += 1.0f;
		}
		if (input->PushKey(DIK_S)) {
			axis.y -= 1.0f;
		}

		const float length = std::sqrt(axis.x * axis.x + axis.y * axis.y);
		if (length > 1.0f) {
			axis.x /= length;
			axis.y /= length;
		}
	}

	return axis;
}

void InputAction::AddBinding(Action action, const InputBinding& binding) { m_bindings[ToIndex(action)].push_back(binding); }
