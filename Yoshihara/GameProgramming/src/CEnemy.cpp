#include "CEnemy.h"

//定数の定義
//左、右、下、上　敵テクスチャマッピング
//移動
#define TEX_LEFTMOVE1 0,600,1200,600
#define TEX_LEFTMOVE2 600,1200,1200,600
#define TEX_LEFTMOVE3 1200,1800,1200,600
#define TEX_LEFTMOVE4 1800,2400,1200,600
#define TEX_RIGHTMOVE1 600,0,1200,600
#define TEX_RIGHTMOVE2 1200,600,1200,600
#define TEX_RIGHTMOVE3 1800,1200,1200,600
#define TEX_RIGHTMOVE4 2400,1800,1200,600
//待機
#define TEX_LEFTWAIT1 0,600,1800,1200
#define TEX_LEFTWAIT2 600,1200,1800,1200
#define TEX_LEFTWAIT3 1200,1800,1800,1200
#define TEX_LEFTWAIT4 1800,2400,1800,1200
#define TEX_RIGHTWAIT1 600,0,1800,1200
#define TEX_RIGHTWAIT2 1200,600,1800,1200
#define TEX_RIGHTWAIT3 1800,1200,1800,1200
#define TEX_RIGHTWAIT4 2400,1800,1800,1200

#define SLIME_BOTTOM 130                    //スライム足元計算用
#define VELOCITY_SLIME 2.0f                 //スライムの移動速度

//static変数の定義
CTexture CEnemy::mTexture;

//メソッドの定義
CTexture* CEnemy::GetTexture()
{
	return &mTexture;
}

//敵のデフォルトコンストラクタ
CEnemy::CEnemy()
	:CCharacter((int)CTaskPriority::Object)
{
}

//敵のコンストラクタ
CEnemy::CEnemy(float x, float y, float w, float h)
	:CEnemy()
{
	Set(x, y, w, h);

	mState = EState::EWAIT;

	Texture(GetTexture(), TEX_LEFTMOVE1);

	mVx = -VELOCITY_SLIME;

	//Time = 0;
}

//デストラクタ
CEnemy::~CEnemy()
{

}

void CEnemy::Death()
{
	//タスクリストから削除
	SetEnabled(false);
}

void CEnemy::Update()
{
	//処理順番を決定
	SetSortOrder(GetY() - SLIME_BOTTOM);
	switch (mState)
	{
	case EState::EWAIT://待機

		WaitAnimation();

		break;
		
	case EState::EMOVE://移動

		//スライムの速度分移動
		SetX(GetX() + mVx);

		MoveAnimation();

		break;
	}

}

//移動アニメーション
void CEnemy::MoveAnimation()
{
	//画像を切り替える速度
	const int PITCH = 64;
	//X座標を保存
	int PosX = (int)GetX();


	//X座標が0以上の時
	if ((int)GetX() >= 0)
	{
		if (PosX % PITCH < PITCH / 4)
		{
			//左移動
			if (mVx < 0.0f)
			{
				Texture(GetTexture(), TEX_LEFTMOVE4);
			}
			//右移動
			else
			{
				Texture(GetTexture(), TEX_RIGHTMOVE1);
			}
		}
		else if (PosX % PITCH < PITCH * 2 / 4)
		{
			//左移動
			if (mVx < 0.0f)
			{
				Texture(GetTexture(), TEX_LEFTMOVE3);
			}
			//右移動
			else
			{
				Texture(GetTexture(), TEX_RIGHTMOVE2);
			}
		}
		else if (PosX % PITCH < PITCH * 3 / 4)
		{
			//左移動
			if (mVx < 0.0f)
			{
				Texture(GetTexture(), TEX_LEFTMOVE2);
			}
			//右移動
			else
			{
				Texture(GetTexture(), TEX_RIGHTMOVE3);
			}
		}
		else
		{
			//左移動
			if (mVx < 0.0f)
			{
				Texture(GetTexture(), TEX_LEFTMOVE1);
			}
			//右移動
			else
			{
				Texture(GetTexture(), TEX_RIGHTMOVE4);
			}
		}
	}
	//X座標が0未満の時
	else
	{	
		//正数にする
		PosX = -PosX;

		if (PosX % PITCH < PITCH / 4)
		{
			//左移動
			if (mVx < 0.0f)
			{
				Texture(GetTexture(), TEX_LEFTMOVE1);
			}
			//右移動
			else
			{
				Texture(GetTexture(), TEX_RIGHTMOVE4);
			}
		}
		else if (PosX % PITCH < PITCH * 2 / 4)
		{
			//左移動
			if (mVx < 0.0f)
			{
				Texture(GetTexture(), TEX_LEFTMOVE2);
			}
			//右移動
			else
			{
				Texture(GetTexture(), TEX_RIGHTMOVE3);
			}
		}
		else if (PosX % PITCH < PITCH * 3 / 4)
		{
			//左移動
			if (mVx < 0.0f)
			{
				Texture(GetTexture(), TEX_LEFTMOVE3);
			}
			//右移動
			else
			{
				Texture(GetTexture(), TEX_RIGHTMOVE2);
			}
		}
		else
		{
			//左移動
			if (mVx < 0.0f)
			{
				Texture(GetTexture(), TEX_LEFTMOVE4);
			}
			//右移動
			else
			{
				Texture(GetTexture(), TEX_RIGHTMOVE1);
			}
		}
	}

}

void CEnemy::WaitAnimation()
{
	//画像を切り替える速度
	const int PITCH = 64;

	mTime++;

	if (mTime % PITCH < PITCH / 4)
	{
		//左向き待機
		if (mVx < 0.0f)
		{
			Texture(GetTexture(), TEX_LEFTWAIT1);
		}
		//右向き待機
		else
		{
			Texture(GetTexture(), TEX_RIGHTWAIT1);
		}
	}
	else if (mTime % PITCH < PITCH * 2 / 4)
	{
		//左向き待機
		if (mVx < 0.0f)
		{
			Texture(GetTexture(), TEX_LEFTWAIT2);
		}
		//右向き待機
		else
		{
			Texture(GetTexture(), TEX_RIGHTWAIT2);
		}
	}
	else if (mTime % PITCH < PITCH * 3 / 4)
	{
		//左向き待機
		if (mVx < 0.0f)
		{
			Texture(GetTexture(), TEX_LEFTWAIT3);
		}
		//右向き待機
		else
		{
			Texture(GetTexture(), TEX_RIGHTWAIT3);
		}
	}
	else
	{
		//左向き待機
		if (mVx < 0.0f)
		{
			Texture(GetTexture(), TEX_LEFTWAIT4);
		}
		//右向き待機
		else
		{
			Texture(GetTexture(), TEX_RIGHTWAIT4);
		}
	}
}

