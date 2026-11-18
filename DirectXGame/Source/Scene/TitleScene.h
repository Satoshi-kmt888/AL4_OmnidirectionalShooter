#pragma once

#include "IScene.h"

#include <memory>

class InputAction;
class WipeManager;

/// <summary>
/// タイトルシーン
/// </summary>
class TitleScene : public IScene {
public:
	// 状態
	enum class State {
		STATE_OPENING,
		STATE_MAIN,
		STATE_CLOSING,
	};

	//=========================================================
	// public methods
	//=========================================================

	TitleScene();
	~TitleScene() override;

	void Enter() override;
	void Update() override;
	void Draw() override;
	void Exit() override;

private:
	//=========================================================
	// private methods
	//=========================================================

	void DrawModel();
	void DrawSprite();

	void ControlImGui();

	void ChangeState();

	//=========================================================
	// private variables
	//=========================================================

	State m_state = State::STATE_OPENING;

	std::unique_ptr<InputAction> m_input;

	/*--- 演出 ---*/

	// ワイプ
	std::unique_ptr<WipeManager> m_wipe;
	float m_wipe_duration = 0.8f;
};
