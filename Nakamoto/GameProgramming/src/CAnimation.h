#pragma once

enum class CAnimationNumber
{
	Move1,
	Move2,
	Move3,
	Move4,
	Move5,
	Move6,
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
	/// <param name="speed">移動速度</param>
	/// <param name="limit">モーションの数</param>
	int MoveAnimation(int x, int y, 
		bool moveX, bool moveY, float speed,int limit);

	int WaitAnimation(int limit);

private:
	//アニメーションの番号
	int AnimationNum;
	//フレームカウンタ
	int mFrame;
};
