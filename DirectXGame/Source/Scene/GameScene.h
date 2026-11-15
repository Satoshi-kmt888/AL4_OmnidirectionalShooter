#pragma once

#include "IScene.h"

#include <3d/Camera.h>
#include <memory>

namespace KamataEngine {
class Input;
class AxisIndicator;
} // namespace KamataEngine

class InputAction;
class DebugCamera;
class WipeManager;
class Skysphere;
class Ground;
class Player;
class CameraController;

/// <summary>
/// ゲームシーン
/// </summary>
class GameScene : public IScene {
public:
	// 状態
	enum class State {
		STATE_OPENING,
		STATE_GAME,
		STATE_CLOSING,
	};

	//=========================================================
	// public methods
	//=========================================================

	GameScene();
	~GameScene();

	void Enter() override;
	void Update() override;
	void Draw() override;
	void Exit() override;

private:
	//=========================================================
	// private methods
	//=========================================================

	// デバッグカメラを含めるカメラの更新処理
	void UpdateCamera();

	// オブジェクトごとの描画処理
	void DrawModel();  // モデル描画
	void DrawSprite(); // スプライト描画

	// ImGui操作
	void ControlImGui();

	// 状態遷移
	void ChangeState();

	//=========================================================
	// private variables
	//=========================================================

	State m_state = State::STATE_OPENING;

	// 入力
	std::unique_ptr<InputAction> m_input_action;

	// カメラ
	KamataEngine::Camera m_camera{};

	KamataEngine::Input* m_input = nullptr;
	KamataEngine::AxisIndicator* m_axis = nullptr;

	bool m_is_debug_camera_enabled = false; // デバッグカメラの有効化

	/*--- ゲームオブジェクト ---*/

	std::unique_ptr<DebugCamera> m_debug_camera;
	std::unique_ptr<Skysphere> m_skysphere;
	std::unique_ptr<Ground> m_ground;
	std::unique_ptr<Player> m_player;
	std::unique_ptr<CameraController> m_camera_controller;

	/*--- 演出 ---*/

	const float m_wipe_duration = 0.8f;

	std::unique_ptr<WipeManager> m_wipe;
};
