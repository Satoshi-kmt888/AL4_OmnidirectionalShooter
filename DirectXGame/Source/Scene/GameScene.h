#pragma once

#include "IScene.h"

#include <3d/AxisIndicator.h>
#include <3d/Camera.h>

namespace KamataEngine {
class Input;
class AxisIndicator;
} // namespace KamataEngine

class InputAction;
class DebugCamera;
class Skysphere;
class Ground;
class Player;
class CameraController;

/// <summary>
/// ゲームシーン
/// </summary>
class GameScene : public IScene {
public:
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

	void UpdateCamera();

	void DrawModel();
	void DrawSprite();

	void ImGuiControl();

	//=========================================================
	// private variables
	//=========================================================

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
};
