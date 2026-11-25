#include "GameScene.h"

#include "Core/Time.h"
#include "GameObject/Bullet/Bullet.h"
#include "GameObject/Camera/CameraController.h"
#include "GameObject/Camera/DebugCamera.h"
#include "GameObject/Enemy/Enemy.h"
#include "GameObject/Player/Player.h"
#include "GameObject/World/Ground.h"
#include "GameObject/World/SkySphere.h"
#include "Geometry/OBB.h"
#include "Geometry/Sphere.h"
#include "Input/InputAction.h"
#include "Physics/Collision.h"
#include "Wipe/WipeManager.h"

#include <2d/Sprite.h>
#include <3d/AxisIndicator.h>
#include <3d/Model.h>
#include <algorithm>
#include <base/TextureManager.h>
#include <imgui.h>

using namespace KamataEngine;

GameScene::GameScene() = default;

GameScene::~GameScene() = default;

void GameScene::Enter() {
	// 入力処理を初期化
	m_input = std::make_unique<InputAction>();
	m_input->Register();

	// カメラを初期化
	m_camera.Initialize();
	// デバッグカメラを初期化
	m_debug_camera = std::make_unique<DebugCamera>();
	m_debug_camera->Initialize();

#ifdef DEVELOP
	// デバッグ用軸インジケーターを初期化(Developビルドでは常に表示する)
	m_axis = AxisIndicator::GetInstance();
	m_axis->Initialize();
	AxisIndicator::SetTargetCamera(&m_camera);
	AxisIndicator::SetVisible(true);
#endif

	//=========================================================
	// game object
	//=========================================================

	/*--- 天球 ---*/

	m_skysphere = std::make_unique<Skysphere>();
	m_skysphere->Initialize(Model::CreateFromOBJ("skysphere"));

	/*--- 地面 ---*/

	m_ground = std::make_unique<Ground>();
	m_ground->Initialize(Model::CreateFromOBJ("ground"));

	/*--- プレイヤー ---*/

	// モデル群を作成
	Player::ModelGroup player_models{
	    .player = Model::CreateFromOBJ("player"),
	    .bullet = Model::CreateSphere(),
	};

	m_player = std::make_unique<Player>();
	m_player->Initialize(m_input.get(), player_models);

	/*--- カメラコントローラー ---*/

	m_camera_controller = std::make_unique<CameraController>();
	m_camera_controller->Initialize(&m_camera);
	m_camera_controller->SetTarget(&m_player->GetWorldTransform());

	/*--- 敵 ---*/

	Enemy::SetModel(Model::CreateFromOBJ("axis"));
	m_enemies.resize(k_max_enemy);
	for (uint32_t i = 0; i < k_max_enemy; ++i) {
		m_enemies[i] = std::make_unique<Enemy>();
		m_enemies[i]->Initialize();
	}

	//=========================================================
	// effect
	//=========================================================

	/*--- ワイプ ---*/

	m_wipe = std::make_unique<WipeManager>();
	m_wipe->Start(WipeType::TYPE_GRID, WipeState::STATE_FADE_OUT, m_wipe_duration, TextureManager::Load("white1x1.png"));
}

void GameScene::Update() {
	// 入力状態を更新
	m_input->Update();

	// 状態遷移
	ChangeState();

	// imgui操作
	ControlImGui();

	m_wipe->Update();

	// 天球を更新
	m_skysphere->Update();
	m_ground->Update();

	m_player->Update();
	m_camera_controller->Update();

	m_enemy_spawn_timer = std::clamp(m_enemy_spawn_timer - Time::GetInstance()->GetDeltaTime(), 0.0f, m_enemy_spawn_cool_time);
	if (m_enemy_spawn_timer <= 0.0f) {
		for (const auto& enemy : m_enemies) {
			if (!enemy->IsAlive()) {
				m_enemy_spawn_timer = m_enemy_spawn_cool_time;
				enemy->Spawn();
				break;
			}
		}
	}

	for (const auto& enemy : m_enemies) {
		if (enemy) {
			enemy->ApprochTarget(m_player->GetWorldTransform().translation_);
			enemy->Update();
		}
	}

	// カメラを更新
	UpdateCamera();

	// ゲームオブジェクトの更新処理が終わってから当たり判定
	CheckCollisions();

#ifdef DEVELOP
	if (m_axis) {
		// 軸表示を更新
		m_axis->Update();
	}
#endif
}

void GameScene::Draw() {
	DrawModel();
	DrawSprite();

#ifdef DEVELOP
	if (m_axis) {
		// 軸表示を描画
		m_axis->Draw();
	}
#endif
}

void GameScene::Exit() {
#ifdef DEVELOP
	if (m_axis) {
		AxisIndicator::Terminate();
	}
#endif
}

void GameScene::UpdateCamera() {
#ifdef DEVELOP
	// デバッグカメラを有効化するか
	if (m_input->IsTrigger(Action::ACTION_DEBUG)) {
		m_is_debug_camera_enabled = !m_is_debug_camera_enabled;
	}

	// デバッグカメラが有効なら
	if (m_is_debug_camera_enabled) {
		m_debug_camera->Update();
		m_camera.matView = m_debug_camera->GetCamera().matView;
		m_camera.matProjection = m_debug_camera->GetCamera().matProjection;
		m_camera.TransferMatrix();

		// デバッグカメラのデータを使用するのでリターンする
		return;
	}
#endif

	m_camera.UpdateMatrix();
}

void GameScene::DrawModel() {
	// モデル描画前処理
	Model::PreDraw();
	//-------------------------

	// 天球を描画
	m_skysphere->Draw(&m_camera);
	m_ground->Draw(&m_camera);

	m_player->Draw(&m_camera);

	for (const auto& enemy : m_enemies) {
		if (enemy) {
			enemy->Draw(&m_camera);
		}
	}

	//-------------------------
	// モデル描画後処理
	Model::PostDraw();
}

void GameScene::DrawSprite() {
	// モデル描画前処理
	Sprite::PreDraw();
	//-------------------------

	// ワイプは最後に描画
	m_wipe->Draw();

	//-------------------------
	// モデル描画後処理
	Sprite::PostDraw();
}

void GameScene::ControlImGui() {
// ゲームシーンのImGui操作はここに集約する
#ifdef USE_IMGUI
	ImGui::Begin("GameScene");
	if (ImGui::CollapsingHeader("Common")) {
		// 敵のスポーン
		if (ImGui::Button("Enemy Spawn")) {
			for (const auto& enemy : m_enemies) {
				if (!enemy || !enemy->IsAlive()) {
					enemy->Spawn();
					break;
				}
			}
		}
	}

	m_camera_controller->ControlImGui();
	m_player->ControlImGui();
	ImGui::End();
#endif
}

void GameScene::ChangeState() {
	switch (m_state) {
		using enum State;
	case STATE_OPENING:
		if (m_wipe->IsFinished()) {
			m_state = STATE_GAME;
		}
		break;
	case STATE_GAME:
		if (!m_player->IsAlive()) {
			m_wipe->Start(WipeType::TYPE_GRID, WipeState::STATE_FADE_IN, m_wipe_duration, TextureManager::Load("white1x1.png"));
			m_state = STATE_CLOSING;
		}
		break;
	case STATE_CLOSING:
		if (m_wipe->IsFinished()) {
			RequestSceneChange(SceneType::SCENE_TITLE);
		}
		break;
	}
}

void GameScene::CheckCollisions() {
	/*--- 弾と敵 ---*/

	for (size_t bullet_index = 0; bullet_index < m_player->GetMaxBullet(); ++bullet_index) {
		Bullet* bullet = m_player->GetBullet(bullet_index);
		if (!bullet || !bullet->IsAlive()) {
			continue;
		}

		for (const auto& enemy : m_enemies) {
			if (!enemy || !enemy->IsAlive()) {
				continue;
			}

			if (Collision::IsCollision(enemy->GetOBB(), bullet->GetSphere())) {
				bullet->OnCollision();
				enemy->OnCollision();
				break;
			}
		}
	}

	/*--- プレイヤーと敵 ---*/

	for (const auto& enemy : m_enemies) {
		if (!enemy || !enemy->IsAlive()) {
			continue;
		}

		if (Collision::IsCollision(m_player->GetOBB(), enemy->GetOBB())) {
			m_player->OnCollision();
		}
	}
}
