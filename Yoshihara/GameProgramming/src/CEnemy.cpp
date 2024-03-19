#include "CEnemy.h"
#include "CPlayer.h"
#include "CUiFont.h"

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


#define SLIME_BOTTOM 138                    //スライム足元計算用
#define ONI_BOTTOM 240                      //鬼足元計算用 

#define SLIME_SHADOW_WAIT 20               //スライムの待機中の影計算用
#define SLIME_SHADOW_MOVE 40               //スライムの移動中の影計算用
#define SLIME_SHADOW_ATTACK 70             //スライムの攻撃中の影計算用

#define SLIME_SHADOW_SIZE_WAIT 200,180      //スライムの待機中の影の大きさ
#define SLIME_SHADOW_SIZE_MOVE 200,180      //スライムの移動中の影の大きさ
#define SLIME_SHADOW_SIZE_ATTACK 200,180    //スライムの攻撃中の影の大きさ

#define ONI_SHADOW_WAIT 200               //鬼の待機中の影計算用
#define ONI_SHADOW_MOVE 200               //鬼の移動中の影計算用
#define ONI_SHADOW_ATTACK 200             //鬼の攻撃中の影計算用

#define ONI_SHADOW_SIZE_WAIT 200,100      //鬼の待機中の影の大きさ
#define ONI_SHADOW_SIZE_MOVE 200,100      //鬼の移動中の影の大きさ
#define ONI_SHADOW_SIZE_ATTACK 200,100    //鬼の攻撃中の影の大きさ

//敵の移動速度
#define VELOCITY_ENEMY_X 2.0f                
#define VELOCITY_ENEMY_Y 1.0f
//敵の撃破ポイント
#define SLIME_POINT 1000
#define ONI_POINT 2000

//static変数の定義
CTexture CEnemy::mTextureSlime;
CTexture CEnemy::mTextureOni;
int CEnemy::mEnemyCount = 0;

//メソッドの定義
CTexture* CEnemy::GetTextureSlime()
{
	return &mTextureSlime;
}

CTexture* CEnemy::GetTextureOni()
{
	return &mTextureOni;
}

int CEnemy::GetEnemyCount()
{
	return mEnemyCount;
}

void CEnemy::ZeroEnemyCount()
{
	mEnemyCount = 0;
}

void CEnemy::PlusEnemyCount()
{
	mEnemyCount++;
}

//敵のデフォルトコンストラクタ
CEnemy::CEnemy()
	:CCharacter((int)CTaskPriority::Object)
	, mColider(this, &mX, &mY, &mZ, 140, 90)
	, mFrame(0)
	//敵がプレイヤーに近づける距離
	, RandomX(rand() % 100 + 50)//50から100未満まででランダム
	, RandomY(rand() % 50 + 50)//50から100未満まででランダム
	//行動の間隔
	, RandomTiming(rand() % 100 + 150)//250から500未満まででランダム
{
}

//敵のコンストラクタ
CEnemy::CEnemy(float x, float y, float w, float h, int hp, EEnemyType enemyType)
	:CEnemy()
{
	Set(x, y, w, h);

	SetHp(hp);

	mState = EState::EWAIT;

	mVx = VELOCITY_ENEMY_X;

	mVy = VELOCITY_ENEMY_Y;

	mEnemyType = enemyType;
	//スライムなら
	if (mEnemyType == EEnemyType::Slime)
	{
		//スライムの画像
		Texture(GetTextureSlime(), TEX_LEFT1, TEX_WAIT);
		//足元計算用にスライムを入れる
		mLeg = SLIME_BOTTOM;	
		
		SetZ(GetY() - SLIME_BOTTOM);
		//攻撃アニメーション数
		AttackNum = 4;
		//移動アニメーション数
		MoveNum = 4;
		//待機アニメーション数
		WaitNum = 4;

		mpShadow = new CShadow(GetX(), GetShadowPosY(), SLIME_SHADOW_SIZE_WAIT);
	}
	//鬼なら
	if (mEnemyType == EEnemyType::Oni)
	{
		//鬼の画像
		Texture(GetTextureOni(), TEX_LEFT1, TEX_WAIT);
		//足元計算用に鬼を入れる
		mLeg = ONI_BOTTOM;

		SetZ(GetY() - ONI_BOTTOM);
		//攻撃アニメーション数
		AttackNum = 6;
		//移動アニメーション数
		MoveNum = 5;
		//待機アニメーション数
		WaitNum = 4;

		mpShadow = new CShadow(GetX(), GetShadowPosY(), ONI_SHADOW_SIZE_WAIT);
	}

}

void CEnemy::Update()
{
	//離れた敵は消去する
	if (CPlayer::GetInstance()->GetX() - GetX() > 1920 || CPlayer::GetInstance()->GetX() - GetX() < -1920)
	{
		SetEnabled(false);
	}
	//処理順番を決定
	SetSortOrder(GetY() - mLeg);
	switch (mState)
	{
	case EState::EWAIT://待機
		
		if (mEnemyType == EEnemyType::Slime)
		{
			//影の高さ
			mShadow = SLIME_SHADOW_WAIT;
			//影の大きさ
			mpShadow->SetShadow(GetX(), GetShadowPosY(), SLIME_SHADOW_SIZE_WAIT);
		}
		else
		{
			//影の高さ
			mShadow = ONI_SHADOW_WAIT;
			//影の大きさ
			mpShadow->SetShadow(GetX(), GetShadowPosY(), ONI_SHADOW_SIZE_WAIT);
		}


		//移動できるようになるとステータスが移動になる
		Move();
		//待機アニメーション
		WaitAnimation(WaitNum);
		//アニメーションを設定
		SetAnimation();

		break;
		
	case EState::EMOVE://移動

		if (mEnemyType == EEnemyType::Slime)
		{
			//影の高さ
			mShadow = SLIME_SHADOW_MOVE;
			//影の大きさ
			mpShadow->SetShadow(GetX(), GetShadowPosY(), SLIME_SHADOW_SIZE_MOVE);
		}
		else
		{
			//影の高さ
			mShadow = ONI_SHADOW_MOVE;
			//影の大きさ
			mpShadow->SetShadow(GetX(), GetShadowPosY(), ONI_SHADOW_SIZE_MOVE);
		}

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
	const int MoveInterval = 250;
	int frame = mFrame++;
	int move;


	//frame/MoveIntervalのあまりがRandomTimingの倍数なら
	if (frame % MoveInterval % RandomTiming == 0)
	{
			mState = EState::EMOVE;
	}

	//ステータスが移動なら移動処理
	if (mState == EState::EMOVE)
	{
		//プレイヤーが右にいるなら右に移動
		if (CPlayer::GetInstance()->GetX() - GetX() > RandomX)
		{
			//mVxが負の数なら正数にする
			if (mVx < 0)
			{
				mVx = -mVx;
			}
			SetX(GetX() + mVx);
			isMoveX = true;
			isMove = true;
		}
		//プレイヤーが左にいるなら左に移動
		else if (CPlayer::GetInstance()->GetX() - GetX() < -RandomX)
		{
			//mVxが正数なら負の数にする
			if (mVx > 0)
			{
				mVx = -mVx;
			}
			SetX(GetX() + mVx);
			isMoveX = true;
			isMove = true;
		}
		else
		{
			isMoveX = false;
		}
		//プレイヤーが上にいるなら上に移動
		if (CPlayer::GetInstance()->GetUnderPosY() - GetUnderPosY() > RandomY)
		{
			//mVyが負の数なら正数にする
			if (mVy < 0)
			{
				mVy = -mVy;
			}
			SetY(GetY() + mVy);
			SetZ(GetY() - SLIME_BOTTOM);
			isMoveY = true;
			isMove = true;
		}
		//プレイヤーが下にいるなら下に移動
		else if (CPlayer::GetInstance()->GetUnderPosY() - GetUnderPosY() < -RandomY)
		{
			//mVyが正数なら負の数にする
			if (mVy > 0)
			{
				mVy = -mVy;
			}
			SetY(GetY() + mVy);
			SetZ(GetY() - SLIME_BOTTOM);
			isMoveY = true;
			isMove = true;
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

//デストラクタ
CEnemy::~CEnemy()
{
	mEnemyCount--;
	if (mHp <= 0)
	{
		if (mEnemyType == EEnemyType::Oni)
		{
			CUiFont::GetInstance()->SetScore(ONI_POINT);
		}
		else
		{
			CUiFont::GetInstance()->SetScore(SLIME_POINT);
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
		//右向き
		if (mVx > 0.0f)
		{
			if (mAnimationNum == CAnimationNumber::Move1)     Texture(GetTexture(), TEX_RIGHT1, TEX_WAIT);
			else if (mAnimationNum == CAnimationNumber::Move2)Texture(GetTexture(), TEX_RIGHT2, TEX_WAIT);
			else if (mAnimationNum == CAnimationNumber::Move3)Texture(GetTexture(), TEX_RIGHT3, TEX_WAIT);
			else                                              Texture(GetTexture(), TEX_RIGHT4, TEX_WAIT);
		}
		//左向き
		else
		{
			if (mAnimationNum == CAnimationNumber::Move1)     Texture(GetTexture(), TEX_LEFT1, TEX_WAIT);
			else if (mAnimationNum == CAnimationNumber::Move2)Texture(GetTexture(), TEX_LEFT2, TEX_WAIT);
			else if (mAnimationNum == CAnimationNumber::Move3)Texture(GetTexture(), TEX_LEFT3, TEX_WAIT);
			else                                              Texture(GetTexture(), TEX_LEFT4, TEX_WAIT);
		}
		break;

	case EState::EMOVE://移動アニメーション
		//右移動
		if (mVx > 0.0f)
		{
			if (mAnimationNum == CAnimationNumber::Move1)     Texture(GetTexture(), TEX_RIGHT1, TEX_MOVE);
			else if (mAnimationNum == CAnimationNumber::Move2)Texture(GetTexture(), TEX_RIGHT2, TEX_MOVE);
			else if (mAnimationNum == CAnimationNumber::Move3)Texture(GetTexture(), TEX_RIGHT3, TEX_MOVE);
			else                                              Texture(GetTexture(), TEX_RIGHT4, TEX_MOVE);
		}
		//左移動
		else
		{
			if (mAnimationNum == CAnimationNumber::Move1)     Texture(GetTexture(), TEX_LEFT1, TEX_MOVE);
			else if (mAnimationNum == CAnimationNumber::Move2)Texture(GetTexture(), TEX_LEFT2, TEX_MOVE);
			else if (mAnimationNum == CAnimationNumber::Move3)Texture(GetTexture(), TEX_LEFT3, TEX_MOVE);
			else                                              Texture(GetTexture(), TEX_LEFT4, TEX_MOVE);
		}
		break;
	}
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

