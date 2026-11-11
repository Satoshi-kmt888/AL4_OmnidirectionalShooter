#include "Game.h"

#include "Core/Clock.h"
#include "Scene/SceneManager.h"

#include <2d/ImGuiManager.h>
#include <base/DirectXCommon.h>
#include <imgui.h>
#include <KamataEngine.h>

using namespace KamataEngine;

Game::Game() = default;

Game::~Game() = default;

bool Game::Initialize() {
	// エンジン本体を初期化
	KamataEngine::Initialize(k_title);

	// DirectX基盤クラスのインスタンスを取得
	m_dx_common = DirectXCommon::GetInstance();
	if (!m_dx_common) {
		return false;
	}

#ifdef USE_IMGUI
	// ImGui管理クラスのインスタンスを取得
	m_imgui = ImGuiManager::GetInstance();
	if (!m_imgui) {
		return false;
	}
#endif

	// Δタイム用クロックインスタンスを取得
	m_clock = Clock::GetInstance();

	// シーンを初期化
	m_scene = std::make_unique<SceneManager>();
	m_scene->Initialize();

	// 初期化が問題なく完了したため初期化フラグを立てる
	m_initialized = true;
	return true;
}

void Game::Run() {
	// エンジンの更新処理が成功し続ける限りループを続ける
	while (!KamataEngine::Update()) {
		// Δタイムを更新
		m_clock->Update();

		// 更新・描画を別関数にまとめ、ここで実行
		if (m_clock->IsFixedUpdateRequired()) {
			this->Update();
			this->Draw();
		}
	}
}

void Game::Finalize() {
	// エンジン未初期化時に終了処理を実行しないよう早期リターン
	if (!m_initialized) {
		return;
	}

	// エンジンを終了させる
	KamataEngine::Finalize();

	// ダングリングポインタ防止
	m_imgui = nullptr;
	m_dx_common = nullptr;
}

void Game::Update() {
#ifdef USE_IMGUI
	// ImGui受付開始
	m_imgui->Begin();
#endif
	//------------------------------

#ifdef USE_IMGUI
	ImGui::Begin("Game");
	// Δタイムを表示
	ImGui::Text("delta_time = %f", m_clock->GetDeltaTime());
	ImGui::End();
#endif

	// シーンを更新
	m_scene->Update();

	//------------------------------
#ifdef USE_IMGUI
	// ImGui受付終了
	m_imgui->End();
#endif
}

void Game::Draw() {
	// DirectXによる描画前処理
	m_dx_common->PreDraw();
	//------------------------------

	// シーンを描画
	m_scene->Draw();

#ifdef USE_IMGUI
	// 更新処理で溜めたImGuiを描画する
	m_imgui->Draw();
#endif

	//------------------------------
	// DirectXによる描画後処理
	m_dx_common->PostDraw();
}