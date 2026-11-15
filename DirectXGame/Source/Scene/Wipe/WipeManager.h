#pragma once

#include "IWipe.h"

#include <memory>

/// <summary>
/// ワイプの種類
/// </summary>
enum class WipeType {
	TYPE_GRID,
};

/// <summary>
/// ワイプマネージャー
/// </summary>
class WipeManager {
public:
	//==================================================
	// public methods
	//==================================================

	WipeManager();
	~WipeManager();

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw();

	/// <summary>
	/// 指定したワイプを開始する
	/// </summary>
	/// <param name="type">種類</param>
	/// <param name="state">状態</param>
	/// <param name="duration">継続時間</param>
	void Start(WipeType type, WipeState state, float duration, uint32_t texture_handle);

	/// <summary>
	/// 終了確認
	/// </summary>
	/// <returns></returns>
	bool IsFinished() const;

private:
	//==================================================
	// private variables
	//==================================================

	// 現在のワイプ
	std::unique_ptr<IWipe> m_current_wipe;
};
