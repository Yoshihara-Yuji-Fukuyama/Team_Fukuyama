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
	, mColider(this, &mX, &mY, 140, 90)
{
	WaitNum = 4;//待機アニメーション数
	MoveNum = 4;//移動アニメーション数
	AttackNum = 4;//攻撃アニメーション数
}

//敵のコンストラクタ
CEnemy::CEnemy(float x, float y, float w, float h)
	:CEnemy()
{
	Set(x, y, w, h);

	mState = EState::EWAIT;

	Texture(GetTexture(), TEX_LEFTMOVE1);

	mVx = -VELOCITY_SLIME;

}


void CEnemy::Collision(CCollider* m, CCollider* o)
{
	float ax, ay;
	//コライダのmとoが衝突しているか判定しているか判定
	if (CCollider::Collision(m, o, &ax, &ay))
	{
		//プレイヤーとの衝突判定を実行(めり込まない処理)
		SetX(GetX() + ax);
		SetY(GetY() + ay);
	}
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

		//待機アニメーション
		AnimSetNum = WaitAnimation(WaitNum);
		//アニメーションを設定
		SetAnimation();

		break;
		
	case EState::EMOVE://移動

		//スライムの速度分移動
		SetX(GetX() + mVx);
		isMoveX = true;

		//移動アニメーション
		AnimSetNum = MoveAnimation(GetX(), GetY(), isMoveX, isMoveY, mVx, MoveNum);
		//アニメーションを設定
		SetAnimation();

		break;
	}

}

//アニメーションを設定
void CEnemy::SetAnimation()
{
	switch (mState)
	{
	case EState::EWAIT:
		//左向き
		if (mVx < 0.0f)
		{
			if (AnimSetNum == 1)     Texture(GetTexture(), TEX_LEFTWAIT1);
			else if (AnimSetNum == 2)Texture(GetTexture(), TEX_LEFTWAIT2);
			else if (AnimSetNum == 3)Texture(GetTexture(), TEX_LEFTWAIT3);
			else                     Texture(GetTexture(), TEX_LEFTWAIT4);
		}
		//右向き
		else
		{
			if (AnimSetNum == 1)     Texture(GetTexture(), TEX_RIGHTWAIT1);
			else if (AnimSetNum == 2)Texture(GetTexture(), TEX_RIGHTWAIT2);
			else if (AnimSetNum == 3)Texture(GetTexture(), TEX_RIGHTWAIT3);
			else                     Texture(GetTexture(), TEX_RIGHTWAIT4);
		}

		break;
	case EState::EMOVE:
		//左移動
		if (mVx < 0.0f)
		{
			if (AnimSetNum == 1)     Texture(GetTexture(), TEX_LEFTMOVE1);
			else if (AnimSetNum == 2)Texture(GetTexture(), TEX_LEFTMOVE2);
			else if (AnimSetNum == 3)Texture(GetTexture(), TEX_LEFTMOVE3);
			else                     Texture(GetTexture(), TEX_LEFTMOVE4);
		}
		//右移動
		else
		{
			if (AnimSetNum == 1)     Texture(GetTexture(), TEX_RIGHTMOVE1);
			else if (AnimSetNum == 2)Texture(GetTexture(), TEX_RIGHTMOVE2);
			else if (AnimSetNum == 3)Texture(GetTexture(), TEX_RIGHTMOVE3);
			else                     Texture(GetTexture(), TEX_RIGHTMOVE4);
		}

		break;
	}
}


