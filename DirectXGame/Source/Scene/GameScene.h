#pragma once

#include "IScene.h"

#include <3d/Camera.h>
#include <cstdint>
#include <math/Vector2.h>
#include <memory>
#include <vector>

namespace KamataEngine {
class Input;
class AxisIndicator;
class Sprite;
} // namespace KamataEngine

class InputAction;
class DebugCamera;
class WipeManager;
class Skysphere;
class Ground;
class Player;
class CameraController;
class Enemy;

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

	// 当たり判定
	void CheckCollisions();

	//=========================================================
	// private variables
	//=========================================================

	// 状態
	State m_state = State::STATE_OPENING;

	// 入力
	std::unique_ptr<InputAction> m_input;

	// カメラ
	KamataEngine::Camera m_camera{};
	//デバッグカメラ
	std::unique_ptr<DebugCamera> m_debug_camera;
	bool m_is_debug_camera_enabled = false;

	//デバッグ用軸表示
	KamataEngine::AxisIndicator* m_axis = nullptr;

	/*--- ゲームオブジェクト ---*/

	std::unique_ptr<Skysphere> m_skysphere;
	std::unique_ptr<Ground> m_ground;
	std::unique_ptr<Player> m_player;
	std::unique_ptr<CameraController> m_camera_controller;
	std::vector<std::unique_ptr<Enemy>> m_enemies;

	/*--- 定数 ---*/

	const uint32_t k_max_enemy = 32;
	float m_enemy_spawn_cool_time = 3.0f;
	float m_enemy_spawn_timer = 0.0f;

	/*--- 演出 ---*/

	//ワイプ
	std::unique_ptr<WipeManager> m_wipe;
	const float m_wipe_duration = 0.8f;

	/*--- UI ---*/

	//プレイヤーライフ
	std::vector<std::unique_ptr<KamataEngine::Sprite>> m_sprites_player_life;
	KamataEngine::Vector2 m_sprite_player_life_pos = {48.0f, 640.0f};
	float m_sprite_player_life_pos_interval = 32.0f;
	KamataEngine::Vector2 m_sprite_player_size = {64.0f, 64.0f};
};
