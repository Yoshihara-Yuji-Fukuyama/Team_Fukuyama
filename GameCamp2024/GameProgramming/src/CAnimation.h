#pragma once

enum class CAnimationNumber
{
	Move1,
	Move2,
	Move3,
	Move4,
	Move5,
	Move6,
	END
};

class CAnimation
{
public:
	CAnimation();

	/// <summary>
	/// 移動アニメーション
	/// </summary>
	/// <param name="x">X座標</param>
	/// <param name="y">Y座標</param>
	/// <param name="moveX">Xが動いているか</param>
	/// <param name="moveY">Yが動いているか</param>
	/// <param name="direction">向き</param>
	/// <param name="limit">モーションの数</param>
	/// <returns>アニメーション番号</returns>
	void MoveAnimation(int x, int y, 
		bool moveX, bool moveY, float direction,int limit);

	/// <summary>
	/// 待機アニメーション
	/// </summary>
	/// <param name="limit">モーションの数</param>
	/// <returns>アニメーション番号</returns>
	void WaitAnimation(int limit);

	/// <summary>
	/// ジャンプアニメーション
	/// </summary>
	/// <param name="y">Y座標</param>
	/// <param name="jump">ジャンプ前の座標</param>
	/// <param name="limit">モーションの数</param>
	/// <returns>アニメーション番号</returns>
	void JumpAnimation(int y, float jump, int limit);

	/// <summary>
	/// 待機アニメーション
	/// </summary>
	/// <param name="limit">モーションの数</param>
	void AttackAnimation(int limit);

	/// <summary>
    /// やられモーション
    /// </summary>
    /// <param name="limit">アニメーション番号</param>
	void HitAnimation(int limit);

	/// <summary>
    /// 防御モーション
    /// </summary>
    /// <param name="limit">アニメーション番号</param>
	void GuardAnimation(int limit);

protected:
	//アニメーション番号
	CAnimationNumber mAnimationNum;
	//フレームカウンタ
	int mFrame;
private:

};
