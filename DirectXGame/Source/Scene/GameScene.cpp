#include "GameScene.h"

#include "GameObject/Camera/DebugCamera.h"
#include "GameObject/Player/Player.h"
#include "GameObject/World/SkySphere.h"

#include <2d/Sprite.h>
#include <3d/AxisIndicator.h>
#include <3d/Model.h>
#include <input/Input.h>

using namespace KamataEngine;

GameScene::GameScene() = default;

GameScene::~GameScene() = default;

void GameScene::Enter() {
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
	m_player->Initialize(Model::CreateFromOBJ("cube"));
}

void GameScene::Update() {
	// カメラを更新
	UpdateCamera();

	// 天球を更新
	m_skysphere->Update();

	m_player->Update();

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
	//デバッグカメラを有効化するか
	if (m_input->TriggerKey(DIK_F1)) {
		m_is_debug_camera_enabled = !m_is_debug_camera_enabled;
	}

	//デバッグカメラが有効なら
	if (m_is_debug_camera_enabled) {
		m_debug_camera->Update();
		m_camera.matView = m_debug_camera->GetCamera().matView;
		m_camera.matProjection = m_debug_camera->GetCamera().matProjection;
		m_camera.TransferMatrix();

		//デバッグカメラのデータを使用するのでリターンする
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
