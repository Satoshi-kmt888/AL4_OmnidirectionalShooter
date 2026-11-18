#include "TitleScene.h"

#include "Input/InputAction.h"
#include "Wipe/WipeManager.h"

#include <2d/Sprite.h>
#include <3d/Model.h>
#include <base/Texturemanager.h>
#include <imgui.h>

using namespace KamataEngine;

TitleScene::TitleScene() = default;

TitleScene::~TitleScene() = default;

void TitleScene::Enter() {
	m_input = std::make_unique<InputAction>();
	m_input->Register();

	//=========================================================
	// effect
	//=========================================================

	/*--- ワイプ ---*/

	m_wipe = std::make_unique<WipeManager>();
	m_wipe->Start(WipeType::TYPE_GRID, WipeState::STATE_FADE_OUT, m_wipe_duration, TextureManager::Load("white1x1.png"));
}

void TitleScene::Update() {
	// 入力状態を更新
	m_input->Update();

	ChangeState();

	ControlImGui();

	m_wipe->Update();
}

void TitleScene::Draw() {
	DrawModel();
	DrawSprite();
}

void TitleScene::Exit() {}

void TitleScene::DrawModel() {
	// モデル描画前処理
	Model::PreDraw();
	//-------------------------

	//-------------------------
	// モデル描画後処理
	Model::PostDraw();
}

void TitleScene::DrawSprite() {
	// スプライト描画前処理
	Sprite::PreDraw();
	//-------------------------

	m_wipe->Draw();

	//-------------------------
	// スプライト描画後処理
	Sprite::PostDraw();
}

void TitleScene::ControlImGui() {
#ifdef USE_IMGUI
	ImGui::Begin("TitleScene");

	ImGui::End();
#endif
}

void TitleScene::ChangeState() {
	switch (m_state) {
		using enum State;
	case STATE_OPENING:
		if (m_wipe->IsFinished()) {
			m_state = STATE_MAIN;
		}
		break;
	case STATE_MAIN:
		if (m_input->IsTrigger(Action::ACTION_DECIDE)) {
			m_wipe->Start(WipeType::TYPE_GRID, WipeState::STATE_FADE_IN, m_wipe_duration, TextureManager::Load("white1x1.png"));
			m_state = STATE_CLOSING;
		}
		break;
	case STATE_CLOSING:
		if (m_wipe->IsFinished()) {
			RequestSceneChange(SceneType::SCENE_GAME);
		}
		break;
	}
}
