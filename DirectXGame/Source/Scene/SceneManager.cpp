#include "SceneManager.h"

#include "GameScene.h"
#include "IScene.h"

#include <optional>

SceneManager::SceneManager() = default;

SceneManager::~SceneManager() = default;

void SceneManager::Initialize() { ChangeScene(k_first_scene); }

void SceneManager::Update() {
	if (!m_current_scene) {
		return;
	}

	m_current_scene->Update();

	// シーンの予約があるか確認する
	if (std::optional<SceneType> next_scene = m_current_scene->GetNextScene(); next_scene.has_value()) {
		// 遷移要求があればシーンを変更
		ChangeScene(next_scene.value());
	}
}

void SceneManager::Draw() {
	if (m_current_scene) {
		m_current_scene->Draw();
	}
}

void SceneManager::ChangeScene(SceneType type) {
	if (m_current_scene) {
		m_current_scene->Exit();
	}

	m_current_scene = CreateScene(type);

	if (m_current_scene) {
		m_current_scene->Enter();
	}
}

std::unique_ptr<IScene> SceneManager::CreateScene(SceneType type) {
	// タイプ別でシーンを生成
	switch (type) {
		using enum SceneType;
	case SCENE_TITLE:
	case SCENE_GAME:
		return std::make_unique<GameScene>();
	}

	return nullptr;
}
