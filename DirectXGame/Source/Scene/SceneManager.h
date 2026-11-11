#pragma once

#include "Scene/SceneType.h"

#include <memory>

class IScene;

/// <summary>
/// 各シーンの処理と遷移を管理するクラス
/// </summary>
class SceneManager {
public:
	//==================================================
	// publice methods
	//==================================================

	SceneManager();
	~SceneManager();

	// コピー・ムーブ禁止
	SceneManager(const SceneManager&) = delete;
	SceneManager& operator=(const SceneManager&) = delete;
	SceneManager(SceneManager&&) = delete;
	SceneManager& operator=(SceneManager&&) = delete;

	void Initialize();
	void Update();
	void Draw();

private:
	//==================================================
	// private methods
	//==================================================

	/// <summary>
	/// シーン遷移
	/// </summary>
	/// <param name="type">シーンの種類</param>
	void ChangeScene(SceneType type);

	/// <summary>
	/// シーンを生成
	/// </summary>
	/// <param name="type">シーンの種類</param>
	/// <returns>生成したシーン</returns>
	std::unique_ptr<IScene> CreateScene(SceneType type);

	//==================================================
	// private variables
	//==================================================

	static inline const SceneType k_first_scene = SceneType::SCENE_GAME;

	std::unique_ptr<IScene> m_current_scene;
};
