#include "GameScene.h"

#include "GameObject/Camera/CameraController.h"
#include "GameObject/Camera/DebugCamera.h"
#include "GameObject/Player/Player.h"
#include "GameObject/World/SkySphere.h"
#include "Input/InputAction.h"

#include <2d/Sprite.h>
#include <3d/AxisIndicator.h>
#include <3d/Model.h>
#include <imgui.h>
#include <input/Input.h>

using namespace KamataEngine;

GameScene::GameScene() = default;

GameScene::~GameScene() = default;

void GameScene::Enter() {
	// 入力処理を初期化
	m_input_action = std::make_unique<InputAction>();
	m_input_action->Register();

	// カメラを初期化
	m_camera.Initialize();

	m_input = Input::GetInstance();

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

	/*--- デバッグカメラ ---*/

	m_debug_camera = std::make_unique<DebugCamera>();
	m_debug_camera->Initialize();

	/*--- 天球 ---*/

	m_skysphere = std::make_unique<Skysphere>();
	m_skysphere->Initialize(Model::CreateFromOBJ("skysphere"));

	/*--- プレイヤー ---*/

	m_player = std::make_unique<Player>();
	m_player->Initialize(m_input_action.get(), Model::CreateFromOBJ("cube"));

	/*--- カメラコントローラー ---*/

	m_camera_controller = std::make_unique<CameraController>();
	m_camera_controller->Initialize(&m_camera);
	m_camera_controller->SetTarget(&m_player->GetWorldTransform());
}

void GameScene::Update() {
	// 入力状態を更新
	m_input_action->Update();

	ImGuiControl();

	// カメラを更新
	UpdateCamera();

	// 天球を更新
	m_skysphere->Update();

	m_player->Update();
	m_camera_controller->Update();

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
	if (m_input->TriggerKey(DIK_F1)) {
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

	m_player->Draw(&m_camera);

	//-------------------------
	// モデル描画後処理
	Model::PostDraw();
}

void GameScene::DrawSprite() {
	// モデル描画前処理
	Sprite::PreDraw();
	//-------------------------

	//-------------------------
	// モデル描画後処理
	Sprite::PostDraw();
}

void GameScene::ImGuiControl() {
// ゲームシーンのImGui操作はここに集約する
#ifdef USE_IMGUI
	ImGui::Begin("GameScene");
	m_camera_controller->ImGuiControl();
	ImGui::End();
#endif
}
