#pragma once

#include <memory>
#include <string>

namespace KamataEngine {
class DirectXCommon;
class ImGuiManager;
} // namespace KamataEngine

class SceneManager;

/// <summary>
/// ゲーム全体の初期化/更新/描画/終了を統括するクラス。
/// </summary>
class Game {
public:
	//==================================================
	// public methods
	//==================================================

	Game();
	~Game();

	// コピー・ムーブ禁止
	Game(const Game&) = delete;
	Game& operator=(const Game&) = delete;
	Game(Game&&) = delete;
	Game& operator=(Game&&) = delete;

	/// <summary>
	/// ゲームの初期化
	/// </summary>
	/// <returns>初期化成功時にtrue</returns>
	bool Initialize();

	/// <summary>
	/// ゲームループ。終了処理を受け取るまでUpdate/Drawを繰り返す。
	/// </summary>
	void Run();

	/// <summary>
	/// 各種システムを終了し、保持しているポインタを破棄する。
	/// </summary>
	void Finalize();

private:
	//==================================================
	// private methods
	//==================================================

	void Update(); // 更新処理
	void Draw();   // 描画処理

	//==================================================
	// private variables
	//==================================================

	// ゲームタイトル
	static inline const std::wstring k_title = L"4WeekJam";

	// エンジン所有クラスへの参照
	KamataEngine::DirectXCommon* m_dx_common = nullptr;
	KamataEngine::ImGuiManager* m_imgui = nullptr;

	// 初期化フラグ
	bool m_initialized = false;

	std::unique_ptr<SceneManager> m_scene;
};