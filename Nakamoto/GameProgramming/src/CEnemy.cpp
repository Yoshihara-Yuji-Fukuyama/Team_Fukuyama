#include "CEnemy.h"
#include "CPlayer.h"

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
#define ONI_BOTTOM 240                      //鬼足元計算用
#define VELOCITY_ENEMY 2.0f                 //敵の移動速度

//static変数の定義
CTexture CEnemy::mTextureSlime;
CTexture CEnemy::mTextureOni;

//メソッドの定義
CTexture* CEnemy::GetTextureSlime()
{
	return &mTextureSlime;
}

CTexture* CEnemy::GetTextureOni()
{
	return &mTextureOni;
}

//敵のデフォルトコンストラクタ
CEnemy::CEnemy()
	:CCharacter((int)CTaskPriority::Object)
	, mColider(this, &mX, &mY, &mZ, 140, 90)
	, mFrame(0)
	,mLif(3)
	, RandomX(rand() % 200)//200まででランダム
	, RandomY(rand() % 100)//100まででランダム
	, RandomTiming(rand() % 500)//500まででランダム
{
}

//敵のコンストラクタ
CEnemy::CEnemy(float x, float y, float w, float h, EEnemyType enemyType)
	:CEnemy()
{
	Set(x, y, w, h);

	mState = EState::EWAIT;

	mVx = VELOCITY_ENEMY;

	mVy = VELOCITY_ENEMY;

	SetZ(GetY() - SLIME_BOTTOM);

	mEnemyType = enemyType;

	if (mEnemyType == EEnemyType::Slime)
	{
		//スライムの画像
		Texture(GetTextureSlime(), TEX_LEFTWAIT1);
		//足元計算用にスライムを入れる
		mLeg = SLIME_BOTTOM;
		//攻撃アニメーション数
		AttackNum = 4;
		//移動アニメーション数
		MoveNum = 4;
		//待機アニメーション数
		WaitNum = 4;
	}

	if (mEnemyType == EEnemyType::Oni)
	{
		//鬼の画像
		Texture(GetTextureOni(), TEX_LEFTWAIT1);
		//足元計算用に鬼を入れる
		mLeg = ONI_BOTTOM;
		//攻撃アニメーション数
		AttackNum = 6;
		//移動アニメーション数
		MoveNum = 5;
		//待機アニメーション数
		WaitNum = 4;
	}

}

//デストラクタ
CEnemy::~CEnemy()
{

}


void CEnemy::Update()
{
	//処理順番を決定
	SetSortOrder(GetY() - mLeg);
	switch (mState)
	{
	case EState::EWAIT://待機

		//移動できるようになるとステータスが移動になる
		Move();
		//待機アニメーション
		WaitAnimation(WaitNum);
		//アニメーションを設定
		SetAnimation();

		break;

	case EState::EMOVE://移動
		//移動処理
		Move();

		//移動アニメーション
		MoveAnimation(GetX(), GetY(), isMoveX, isMoveY, mVx, MoveNum);
		//アニメーションを設定
		SetAnimation();

		break;
	}

}

void CEnemy::Move()
{
	const int MoveInterval = 500;
	int frame = mFrame++;
	int move;


	//frame/MoveIntervalのあまりがRandomTimingの倍数なら
	if (frame % MoveInterval % RandomTiming == 0)
	{
		move = rand();//偶数か奇数をランダム
		//偶数なら移動
		if (move % 2 == 0)
		{
			mState = EState::EMOVE;
		}
		//奇数なら待機
		else
		{
			mState = EState::EWAIT;
		}
	}

	//ステータスが移動なら移動処理
	if (mState == EState::EMOVE)
	{
		//プレイヤーが左にいるなら左に移動
		if (CPlayer::GetInstance()->GetX() - GetX() < -RandomX)
		{
			//mVxが正数なら負の数にする
			if (mVx > 0)
			{
				mVx = -mVx;
				isMoveX = true;
				isMove = true;
			}
			//SetX(GetX() + mVx);
		}
		//プレイヤーが右にいるなら右に移動
		else if (CPlayer::GetInstance()->GetX() - GetX() > RandomX)
		{
			//mVxが負の数なら正数にする
			if (mVx < 0)
			{
				mVx = -mVx;
				isMoveX = true;
				isMove = true;
			}
			//SetX(GetX() + mVx);
		}
		else
		{
			isMoveX = false;
		}

		//プレイヤーが下にいるなら下に移動
		if (CPlayer::GetInstance()->GetUnderPosY() - GetUnderPosY() < -RandomY)
		{
			//mVyが正数なら負の数にする
			if (mVy > 0)
			{
				mVy = -mVy;
				isMoveY = true;
				isMove = true;
			}
			//SetY(GetY() + mVy);
			SetZ(GetY() - SLIME_BOTTOM);
		}
		//プレイヤーが上にいるなら上に移動
		else if (CPlayer::GetInstance()->GetUnderPosY() - GetUnderPosY() > RandomY)
		{
			//mVyが負の数なら正数にする
			if (mVy < 0)
			{
				mVy = -mVy;
				isMoveY = true;
				isMove = true;
			}
			//SetY(GetY() + mVy);
			SetZ(GetY() - SLIME_BOTTOM);
		}
		else
		{
			isMoveY = false;
		}

		//縦も横も移動していないなら待機に移行
		if (isMoveX == false && isMoveY == false)
		{
			isMove = false;
			mState = EState::EWAIT;
		}
	}
}

void CEnemy::Death()
{
	//タスクリストから削除
	SetEnabled(false);
}


//アニメーションを設定
void CEnemy::SetAnimation()
{
	switch (mState)
	{
	case EState::EWAIT://待機アニメーション
		//左向き
		if (mVx < 0.0f)
		{
			if (mAnimationNum == CAnimationNumber::Move1)     Texture(GetTexture(), TEX_LEFTWAIT1);
			else if (mAnimationNum == CAnimationNumber::Move2)Texture(GetTexture(), TEX_LEFTWAIT2);
			else if (mAnimationNum == CAnimationNumber::Move3)Texture(GetTexture(), TEX_LEFTWAIT3);
			else                                              Texture(GetTexture(), TEX_LEFTWAIT4);
		}
		//右向き
		else
		{
			if (mAnimationNum == CAnimationNumber::Move1)     Texture(GetTexture(), TEX_RIGHTWAIT1);
			else if (mAnimationNum == CAnimationNumber::Move2)Texture(GetTexture(), TEX_RIGHTWAIT2);
			else if (mAnimationNum == CAnimationNumber::Move3)Texture(GetTexture(), TEX_RIGHTWAIT3);
			else                                              Texture(GetTexture(), TEX_RIGHTWAIT4);
		}

		break;
	case EState::EMOVE://移動アニメーション
		//左移動
		if (mVx < 0.0f)
		{
			if (mAnimationNum == CAnimationNumber::Move1)     Texture(GetTexture(), TEX_LEFTMOVE1);
			else if (mAnimationNum == CAnimationNumber::Move2)Texture(GetTexture(), TEX_LEFTMOVE2);
			else if (mAnimationNum == CAnimationNumber::Move3)Texture(GetTexture(), TEX_LEFTMOVE3);
			else                                              Texture(GetTexture(), TEX_LEFTMOVE4);
		}
		//右移動
		else
		{
			if (mAnimationNum == CAnimationNumber::Move1)     Texture(GetTexture(), TEX_RIGHTMOVE1);
			else if (mAnimationNum == CAnimationNumber::Move2)Texture(GetTexture(), TEX_RIGHTMOVE2);
			else if (mAnimationNum == CAnimationNumber::Move3)Texture(GetTexture(), TEX_RIGHTMOVE3);
			else                                              Texture(GetTexture(), TEX_RIGHTMOVE4);
		}

		break;
	}
}

void CEnemy::Collision(CCollider* m, CCollider* o)
{
	float ax, ay;
	//コライダのmとoが衝突しているか判定しているか判定

	if (CCollider::Collision(m, o, &ax, &ay ))
	{
		//プレイヤーとの衝突判定を実行(めり込まない処理)
		SetX(GetX() + ax);
		SetY(GetY() + ay);
		mLif--;
		
		if (mLif < 0)
		{
			mEnabled = false;
		}

	}
}

