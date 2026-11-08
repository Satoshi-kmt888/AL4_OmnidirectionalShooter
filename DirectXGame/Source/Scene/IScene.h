#pragma once

#include "Scene/SceneType.h"

#include <optional>

/// <summary>
/// 各シーンのインターフェイスクラス
/// </summary>
class IScene {
public:
	//==================================================
	// public methods
	//==================================================

	virtual ~IScene() = default;

	/// <summary>
	/// 開始処理
	/// </summary>
	virtual void Enter() = 0;

	/// <summary>
	/// 更新処理
	/// </summary>
	virtual void Update() = 0;

	/// <summary>
	/// 描画処理
	/// </summary>
	virtual void Draw() = 0;

	/// <summary>
	/// 終了処理
	/// </summary>
	virtual void Exit() = 0;

	std::optional<SceneType> GetNextScene() const { return next_scene_type_; }

protected:
	//==================================================
	// private methods
	//==================================================

	/// <summary>
	/// シーン遷移を要求
	/// </summary>
	/// <param name="nextScene"></param>
	void RequestSceneChange(SceneType nextScene) { next_scene_type_ = nextScene; }

private:
	//==================================================
	// private variables
	//==================================================

	// シーン変更リクエスト
	std::optional<SceneType> next_scene_type_ = std::nullopt;
};
