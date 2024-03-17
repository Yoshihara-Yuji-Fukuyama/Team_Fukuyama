#include "CEnemy.h"
#include "CPlayer.h"

//確認用
#include <iostream>

//左、右
//左向き
#define TEX_LEFT1 0,600
#define TEX_LEFT2 600,1200
#define TEX_LEFT3 1200,1800
#define TEX_LEFT4 1800,2400
#define TEX_LEFT5 2400,3000
#define TEX_LEFT6 3000,3600
//右向き
#define TEX_RIGHT1 600,0
#define TEX_RIGHT2 1200,600
#define TEX_RIGHT3 1800,1200
#define TEX_RIGHT4 2400,1800
#define TEX_RIGHT5 3000,2400
#define TEX_RIGHT6 3600,3000
//下、上
//移動
#define TEX_MOVE 1200,600
//待機
#define TEX_WAIT 1800,1200


#define SLIME_BOTTOM 130                    //スライム足元計算用
#define ONI_BOTTOM 240                      //鬼足元計算用 
//敵の移動速度
#define VELOCITY_ENEMY_X 2.0f                
#define VELOCITY_ENEMY_Y 1.0f

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
	, mCollider(this, &mX, &mY, &mZ, 140, 90, CCollider::EColliderType::ESLIME)
	, mFrame(0)
	, RandomX(rand() % 200)//200まででランダム
	, RandomY(rand() % 100)//100まででランダム
	, RandomTiming(rand() % 500)//500まででランダム
{
}

//敵のコンストラクタ
CEnemy::CEnemy(float x, float y, float w, float h, int hp,
	EEnemyType enemyType)
	:CEnemy()
{
	Set(x, y, w, h);

	SetHp(hp);

	mState = EState::EWAIT;

	mVx = VELOCITY_ENEMY_X;

	mVy = VELOCITY_ENEMY_Y;

	SetZ(GetY() - SLIME_BOTTOM);

	mEnemyType = enemyType;

	

	if (mEnemyType == EEnemyType::Slime)
	{
		//スライムの画像
		Texture(GetTextureSlime(), TEX_LEFT1, TEX_WAIT);
		//足元計算用にスライムを入れる
		mLeg = SLIME_BOTTOM;
		//攻撃アニメーション数
		AttackNum = 4;
		//移動アニメーション数
		MoveNum = 4;
		//待機アニメーション数
		WaitNum = 4;

		mTag = ETag::ESLIME;
	}

	if (mEnemyType == EEnemyType::Oni)
	{
		//鬼の画像
		Texture(GetTextureOni(), TEX_LEFT1, TEX_WAIT);
		//足元計算用に鬼を入れる
		mLeg = ONI_BOTTOM;
		//攻撃アニメーション数
		AttackNum = 6;
		//移動アニメーション数
		MoveNum = 5;
		//待機アニメーション数
		WaitNum = 4;

		mTag = ETag::ESLIME;
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
			if (mAnimationNum == CAnimationNumber::Move1)     Texture(GetTexture(), TEX_LEFT1, TEX_WAIT);
			else if (mAnimationNum == CAnimationNumber::Move2)Texture(GetTexture(), TEX_LEFT2, TEX_WAIT);
			else if (mAnimationNum == CAnimationNumber::Move3)Texture(GetTexture(), TEX_LEFT3, TEX_WAIT);
			else                                              Texture(GetTexture(), TEX_LEFT4, TEX_WAIT);
		}
		//右向き
		else
		{
			if (mAnimationNum == CAnimationNumber::Move1)     Texture(GetTexture(), TEX_RIGHT1, TEX_WAIT);
			else if (mAnimationNum == CAnimationNumber::Move2)Texture(GetTexture(), TEX_RIGHT2, TEX_WAIT);
			else if (mAnimationNum == CAnimationNumber::Move3)Texture(GetTexture(), TEX_RIGHT3, TEX_WAIT);
			else                                              Texture(GetTexture(), TEX_RIGHT4, TEX_WAIT);
		}

		break;
	case EState::EMOVE://移動アニメーション
		//左移動
		if (mVx < 0.0f)
		{
			if (mAnimationNum == CAnimationNumber::Move1)     Texture(GetTexture(), TEX_LEFT1, TEX_MOVE);
			else if (mAnimationNum == CAnimationNumber::Move2)Texture(GetTexture(), TEX_LEFT2, TEX_MOVE);
			else if (mAnimationNum == CAnimationNumber::Move3)Texture(GetTexture(), TEX_LEFT3, TEX_MOVE);
			else                                              Texture(GetTexture(), TEX_LEFT4, TEX_MOVE);
		}
		//右移動
		else
		{
			if (mAnimationNum == CAnimationNumber::Move1)     Texture(GetTexture(), TEX_RIGHT1, TEX_MOVE);
			else if (mAnimationNum == CAnimationNumber::Move2)Texture(GetTexture(), TEX_RIGHT2, TEX_MOVE);
			else if (mAnimationNum == CAnimationNumber::Move3)Texture(GetTexture(), TEX_RIGHT3, TEX_MOVE);
			else                                              Texture(GetTexture(), TEX_RIGHT4, TEX_MOVE);
		}

		break;
	}
}

CEnemy::EEnemyType CEnemy::GetEnemyType()
{
	return mEnemyType;
}

//衝突判定
void CEnemy::Collision(CCollider *m, CCollider *o)
{
	float ax, ay;

	switch (o->GetCType())
	{
	case CCollider::EColliderType::EPLAYER:

		//コライダのmとoが衝突しているか判定しているか判定
		if (CCollider::Collision(m, o, &ax, &ay))
		{
			//プレイヤーとの衝突判定を実行(めり込まない処理)
			SetX(GetX() + ax);
			SetY(GetY() + ay);
		}
		break;
	case CCollider::EColliderType::EPATTACK1:
		//コライダのmとoが衝突しているか判定しているか判定
		if (CCollider::Collision(m, o, &ax, &ay))
		{
			//プレイヤーとの衝突判定を実行(めり込まない処理)
			SetX(GetX() + 10);
			mHp -= 25;

		}

		std::cout << "HPの値は" << mHp << "です\n";

		if (mHp <= 0)
		{
			mEnabled = false;
		}
		break;
	}
}

