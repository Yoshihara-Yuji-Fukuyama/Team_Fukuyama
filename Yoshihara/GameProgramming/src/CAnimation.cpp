#include "CAnimation.h"


CAnimation::CAnimation()
	:mFrame(0)
{
}

//移動アニメーション
void CAnimation::MoveAnimation(int x, int y, bool moveX, bool moveY, float direction,int limit)
{
	//画像を切り替える速度
	const int PITCH = 192;
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
			if (direction < 0.0f)
			{
				//限界が6なら6から
				if (limit == 6) mAnimationNum = CAnimationNumber::Move6;
				//限界が5なら5から
				else if (limit == 5)mAnimationNum = CAnimationNumber::Move5;
				else mAnimationNum = CAnimationNumber::Move4;
			}
			//右移動
			else
			{
				mAnimationNum = CAnimationNumber::Move1;
			}
		}
		else if (Pos % PITCH < PITCH * 2 / limit)
		{
			//左移動
			if (direction < 0.0f)
			{
				if (limit == 6) mAnimationNum = CAnimationNumber::Move5;
				else if (limit == 5)mAnimationNum = CAnimationNumber::Move4;
				else mAnimationNum = CAnimationNumber::Move3;
			}
			//右移動
			else
			{
				mAnimationNum = CAnimationNumber::Move2;
			}
		}
		else if (Pos % PITCH < PITCH * 3 / limit)
		{
			//左移動
			if (direction < 0.0f)
			{
				if (limit == 6) mAnimationNum = CAnimationNumber::Move4;
				else if (limit == 5)mAnimationNum = CAnimationNumber::Move3;
				else mAnimationNum = CAnimationNumber::Move2;
			}
			//右移動
			else
			{
				mAnimationNum = CAnimationNumber::Move3;
			}
		}
		else if (Pos % PITCH < PITCH * 4 / limit)
		{
			//左移動
			if (direction < 0.0f)
			{
				if (limit == 6) mAnimationNum = CAnimationNumber::Move3;
				else if (limit == 5)mAnimationNum = CAnimationNumber::Move2;
				else mAnimationNum = CAnimationNumber::Move1;
			}
			//右移動
			else
			{
				mAnimationNum = CAnimationNumber::Move4;
			}
		}
		//限界が5以上なら続ける
		else if (Pos % PITCH < PITCH * 5 / limit && limit >= 5)
		{
			//左移動
			if (direction < 0.0f)
			{
				if (limit == 6)mAnimationNum = CAnimationNumber::Move2;
				else mAnimationNum = CAnimationNumber::Move1;
			}
			//右移動
			else
			{
				mAnimationNum = CAnimationNumber::Move5;
			}
		}
		//限界が6以上なら続ける
		else if (limit >= 6)
		{
			//左移動
			if (direction < 0.0f)
			{
				mAnimationNum = CAnimationNumber::Move1;
			}
			//右移動
			else
			{
				mAnimationNum = CAnimationNumber::Move6;
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
			if (direction < 0.0f)
			{
				mAnimationNum = CAnimationNumber::Move1;
			}
			//右移動
			else
			{
				//限界が6なら6からスタート
				if (limit == 6) mAnimationNum = CAnimationNumber::Move6;
				//限界が5なら5から
				else if (limit == 5)mAnimationNum = CAnimationNumber::Move5;
				else mAnimationNum = CAnimationNumber::Move4;
			}
		}
		else if (Pos % PITCH < PITCH * 2 / limit)
		{
			//左移動
			if (direction < 0.0f)
			{
				mAnimationNum = CAnimationNumber::Move2;
			}
			//右移動
			else
			{
				if (limit == 6) mAnimationNum = CAnimationNumber::Move5;
				else if (limit == 5)mAnimationNum = CAnimationNumber::Move4;
				else mAnimationNum = CAnimationNumber::Move3;
			}
		}
		else if (Pos % PITCH < PITCH * 3 / limit)
		{
			//左移動
			if (direction < 0.0f)
			{
				mAnimationNum = CAnimationNumber::Move3;
			}
			//右移動
			else
			{
				if (limit == 6) mAnimationNum = CAnimationNumber::Move4;
				else if (limit == 5)mAnimationNum = CAnimationNumber::Move3;
				else mAnimationNum = CAnimationNumber::Move2;
			}
		}
		else if (Pos % PITCH < PITCH * 4 / limit)
		{
			//左移動
			if (direction < 0.0f)
			{
				mAnimationNum = CAnimationNumber::Move4;
			}
			//右移動
			else
			{
				if (limit == 6) mAnimationNum = CAnimationNumber::Move3;
				else if (limit == 5)mAnimationNum = CAnimationNumber::Move2;
				else mAnimationNum = CAnimationNumber::Move1;
			}
		}
		//限界が5以上なら続ける
		else if (Pos % PITCH < PITCH * 5 / limit && limit >= 5)
		{
			//左移動
			if (direction < 0.0f)
			{
				mAnimationNum = CAnimationNumber::Move5;
			}
			//右移動
			else
			{
				if (limit == 6)mAnimationNum = CAnimationNumber::Move2;
				else if (limit == 5)mAnimationNum = CAnimationNumber::Move1;
			}
		}
		//限界が6以上なら続ける
		else if (limit >= 6)
		{
			//左移動
			if (direction < 0.0f)
			{
				mAnimationNum = CAnimationNumber::Move6;
			}
			//右移動
			else
			{
				mAnimationNum = CAnimationNumber::Move1;
			}
		}
	}
}

//待機アニメーション
void CAnimation::WaitAnimation(int limit)
{
	//画像を切り替える速度
	const int PITCH = 48;
	int frame = mFrame++;

	if (frame % PITCH < PITCH / limit)
	{
		mAnimationNum = CAnimationNumber::Move1;
	}
	else if (frame % PITCH < PITCH * 2 / limit)
	{
		mAnimationNum = CAnimationNumber::Move2;
	}
	else if (frame % PITCH < PITCH * 3 / limit)
	{
		mAnimationNum = CAnimationNumber::Move3;
	}
	else
	{
		mAnimationNum = CAnimationNumber::Move4;
	}
}

//ジャンプアニメーション
void CAnimation::JumpAnimation(int y, float jump, int limit)
{
	//画像を切り替える速度
	const int PITCH = 270;
	//ジャンプ前とジャンプ中の座標の差を求める
	int JumpPos = y - jump;


	if (JumpPos % PITCH < PITCH / limit)
	{
			mAnimationNum = CAnimationNumber::Move1;
	}
	else if (JumpPos % PITCH < PITCH * 2 / limit)
	{
		mAnimationNum = CAnimationNumber::Move2;
	}
	else if (JumpPos % PITCH < PITCH * 3 / limit)
	{
		mAnimationNum = CAnimationNumber::Move3;
	}
	else
	{
		mAnimationNum = CAnimationNumber::Move4;
	}
}


//攻撃アニメーション
void CAnimation::AttackAnimation(int limit)
{
	//画像を切り替える速度
	const int PITCH = 72;
	int frame = mFrame++;

	if (frame % PITCH < PITCH / limit)
	{
		mAnimationNum = CAnimationNumber::Move1;
	}
	else if (frame % PITCH < PITCH * 2 / limit)
	{
		mAnimationNum = CAnimationNumber::Move2;
	}
	else if (frame % PITCH < PITCH * 3 / limit)
	{
		mAnimationNum = CAnimationNumber::Move3;
	}
	else if (frame % PITCH < PITCH * 4 / limit)
	{
		mAnimationNum = CAnimationNumber::Move4;
	}
	else if (frame % PITCH < PITCH * 5 / limit)
	{
		mAnimationNum = CAnimationNumber::Move5;
	}
	else if (frame % PITCH < PITCH * 6 / limit)
	{
		mAnimationNum = CAnimationNumber::Move6;
	}
	else
	{
		mAnimationNum = CAnimationNumber::END;
	}
	return;
}

//やられアニメーション
void CAnimation::DeathAnimation(int limit)
{
	//画像を切り替える速度
	const int PITCH = 12;
	int frame = mFrame++;

	if (frame % PITCH < PITCH / limit)
	{
		mAnimationNum = CAnimationNumber::Move1;
	}
}