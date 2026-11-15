#pragma once

/// <summary>
/// ワイプの状態
/// </summary>
enum class WipeState {
	STATE_NONE,
	STATE_FADE_IN,
	STATE_FADE_OUT,
};

/// <summary>
/// 各ワイプのインターフェイスクラス
/// </summary>
class IWipe {
public:
	//==================================================
	// public methods
	//==================================================

	virtual ~IWipe() = default;

	/// <summary>
	/// ワイプの開始
	/// </summary>
	/// <param name="state"></param>
	/// <param name="duration"></param>
	virtual void Start(WipeState state, float duration) = 0;

	/// <summary>
	/// 更新処理
	/// </summary>
	virtual void Update() = 0;

	/// <summary>
	/// 描画処理
	/// </summary>
	virtual void Draw() = 0;

	/// <summary>
	/// 演出が終了したか
	/// </summary>
	/// <returns></returns>
	virtual bool IsFinished() const = 0;

	/// <summary>
	/// 現在の状態を取得
	/// </summary>
	/// <returns></returns>
	virtual WipeState GetState() const = 0;
};
