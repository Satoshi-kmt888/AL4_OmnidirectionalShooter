#pragma once

#include "IScene.h"

#include <3d/AxisIndicator.h>
#include <3d/Camera.h>

namespace KamataEngine {
class Input;
class AxisIndicator;
}

class DebugCamera;
class Skysphere;
class Player;

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

	//=========================================================
	// private variables
	//=========================================================

	// カメラ
	KamataEngine::Camera m_camera{};

	KamataEngine::Input* m_input = nullptr;
	KamataEngine::AxisIndicator* m_axis = nullptr;

	bool m_is_debug_camera_enabled = false; // デバッグカメラの有効化

	/*--- ゲームオブジェクト ---*/

	std::unique_ptr<DebugCamera> m_debug_camera;
	std::unique_ptr<Skysphere> m_skysphere;
	std::unique_ptr<Player> m_player;
};
