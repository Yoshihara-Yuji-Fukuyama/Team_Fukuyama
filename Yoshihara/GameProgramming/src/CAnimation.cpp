#include "CAnimation.h"


CAnimation::CAnimation()
	:mFrame(0)
{
}

//移動アニメーション
int CAnimation::MoveAnimation(int x, int y, bool moveX, bool moveY, float speed,int limit)
{
	//画像を切り替える速度
	const int PITCH = 64;
	//座標を保存
	int Pos = x;
	//Y座標だけ移動しているならY座標を入れる
	if (moveX == false && moveY == true)
	{
		Pos = y;
	}

	//座標が0以上の時
	if (Pos >= 0)
	{
		if (Pos % PITCH < PITCH / limit)
		{
			//左移動
			if (speed < 0.0f)
			{
				//限界が6なら6からスタート
				if (limit == 6) AnimationNum = (int)CAnimationNumber::Move6;
				else AnimationNum = (int)CAnimationNumber::Move4;
			}
			//右移動
			else
			{
				AnimationNum = (int)CAnimationNumber::Move1;
			}
		}
		else if (Pos % PITCH < PITCH * 2 / limit)
		{
			//左移動
			if (speed < 0.0f)
			{
				if (limit == 6) AnimationNum = (int)CAnimationNumber::Move5;
				else AnimationNum = (int)CAnimationNumber::Move3;
			}
			//右移動
			else
			{
				AnimationNum = (int)CAnimationNumber::Move2;
			}
		}
		else if (Pos % PITCH < PITCH * 3 / limit)
		{
			//左移動
			if (speed < 0.0f)
			{
				if (limit == 6) AnimationNum = (int)CAnimationNumber::Move4;
				else AnimationNum = (int)CAnimationNumber::Move2;
			}
			//右移動
			else
			{
				AnimationNum = (int)CAnimationNumber::Move3;
			}
		}
		else if (Pos % PITCH < PITCH * 4 / limit)
		{
			//左移動
			if (speed < 0.0f)
			{
				if (limit == 6) AnimationNum = (int)CAnimationNumber::Move3;
				else AnimationNum = (int)CAnimationNumber::Move1;
			}
			//右移動
			else
			{
				AnimationNum = (int)CAnimationNumber::Move4;
			}
		}
		//限界が6なら最後まで
		else if (Pos % PITCH < PITCH * 5 / limit && limit == 6)
		{
			//左移動
			if (speed < 0.0f)
			{
				AnimationNum = (int)CAnimationNumber::Move2;
			}
			//右移動
			else
			{
				AnimationNum = (int)CAnimationNumber::Move5;
			}
		}
		else
		{
			//左移動
			if (speed < 0.0f)
			{
				AnimationNum = (int)CAnimationNumber::Move1;
			}
			//右移動
			else
			{
				AnimationNum = (int)CAnimationNumber::Move6;
			}
		}
	}
	//座標が0未満の時
	else
	{
		//正数にする
		Pos = -Pos;

		if (Pos % PITCH < PITCH / limit)
		{
			//左移動
			if (speed < 0.0f)
			{
				AnimationNum = (int)CAnimationNumber::Move1;
			}
			//右移動
			else
			{
				//限界が6なら6からスタート
				if (limit == 6) AnimationNum = (int)CAnimationNumber::Move6;
				else AnimationNum = (int)CAnimationNumber::Move4;
			}
		}
		else if (Pos % PITCH < PITCH * 2 / limit)
		{
			//左移動
			if (speed < 0.0f)
			{
				AnimationNum = (int)CAnimationNumber::Move2;
			}
			//右移動
			else
			{
				if (limit == 6) AnimationNum = (int)CAnimationNumber::Move5;
				else AnimationNum = (int)CAnimationNumber::Move3;
			}
		}
		else if (Pos % PITCH < PITCH * 3 / limit)
		{
			//左移動
			if (speed < 0.0f)
			{
				AnimationNum = (int)CAnimationNumber::Move3;
			}
			//右移動
			else
			{
				if (limit == 6) AnimationNum = (int)CAnimationNumber::Move4;
				else AnimationNum = (int)CAnimationNumber::Move2;
			}
		}
		else if (Pos % PITCH < PITCH * 4 / limit)
		{
			//左移動
			if (speed < 0.0f)
			{
				AnimationNum = (int)CAnimationNumber::Move4;
			}
			//右移動
			else
			{
				if (limit == 6) AnimationNum = (int)CAnimationNumber::Move3;
				else AnimationNum = (int)CAnimationNumber::Move1;
			}
		}
		//限界が6なら最後まで
		else if (Pos % PITCH < PITCH * 5 / limit && limit == 6)
		{
			//左移動
			if (speed < 0.0f)
			{
				AnimationNum = (int)CAnimationNumber::Move5;
			}
			//右移動
			else
			{
				AnimationNum = (int)CAnimationNumber::Move2;
			}
		}
		else
		{
			//左移動
			if (speed < 0.0f)
			{
				AnimationNum = (int)CAnimationNumber::Move6;
			}
			//右移動
			else
			{
				AnimationNum = (int)CAnimationNumber::Move1;
			}
		}
	}
	return AnimationNum;
}

//待機アニメーション
int CAnimation::WaitAnimation(int limit)
{
	//画像を切り替える速度
	const int PITCH = 48;
	int frame = mFrame++;

	if (frame % PITCH < PITCH / limit)
	{
		AnimationNum = (int)CAnimationNumber::Move1;
	}
	else if (frame % PITCH < PITCH * 2 / limit)
	{
		AnimationNum = (int)CAnimationNumber::Move2;
	}
	else if (frame % PITCH < PITCH * 3 / limit)
	{
		AnimationNum = (int)CAnimationNumber::Move3;
	}
	else
	{
		AnimationNum = (int)CAnimationNumber::Move4;
	}
	return AnimationNum;
}