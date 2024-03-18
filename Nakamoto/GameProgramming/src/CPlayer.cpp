#include "CPlayer.h"
#include "CApplication.h"
#include "CCollisionManager.h"

//左、右
//左向き
#define TEX_LEFT1 600,0
#define TEX_LEFT2 1200,600
#define TEX_LEFT3 1800,1200
#define TEX_LEFT4 2400,1800
#define TEX_LEFT5 3000,2400
#define TEX_LEFT6 3600,3000
//右向き
#define TEX_RIGHT1 0,600
#define TEX_RIGHT2 600,1200
#define TEX_RIGHT3 1200,1800
#define TEX_RIGHT4 1800,2400
#define TEX_RIGHT5 2400,3000
#define TEX_RIGHT6 3000,3600

//下、上
//待機
#define TEX_WAIT 3000,2400
//移動
#define TEX_MOVE 2400,1800
//ジャンプ
#define TEX_JUMP 3600,3000
//攻撃1
#define TEX_ATTACK1 600,0
//攻撃2
#define TEX_ATTACK2 1200,600
//攻撃3
#define TEX_ATTACK3 1800,1200

#define PLAYER_STARTSET 100.0f,300.0f,300.0f,300.0f//x,y,w,h プレイヤーの初期位置

#define PLAYER_HP 100                       //プレイヤーのHP
#define VELOCITY_PLAYER 3.0f	            //プレイヤーの移動速度
#define JUMPV0 (30 / 1.4f)		            //ジャンプの初速度
#define GRAVITY (30 / 30)		            //重力加速度
#define PLAYER_BOTTOM 270                   //プレイヤー足元計算用

//static変数の定義
CTexture CPlayer::mTexture;

CPlayer* CPlayer::mpInstance;

//メソッドの定義
CTexture* CPlayer::GetTexture()
{
	return &mTexture;
}

//インスタンスの取得
CPlayer* CPlayer::GetInstance()
{
	if (mpInstance == nullptr)
	{
		mpInstance = new CPlayer(PLAYER_STARTSET, PLAYER_HP);
	}
	return mpInstance;
}

CPlayer::CPlayer()
	:CCharacter((int)CTaskPriority::Object)
	, mCollider(this, &mX, &mY, &mZ, 100, 200, CCollider::EColliderType::EPLAYER)
	, isClick(false)
{
	isAttack = false;
	isAttackNext = false;
	mState = EState::EWAIT;
	WaitNum = 4;//待機アニメーション数
	MoveNum = 6;//移動アニメーション数
	JumpNum = 4;//ジャンプアニメーション数
	AttackNum = 6;//攻撃1アニメーション数+1
	AttackNum2 = 6;//攻撃2アニメーション数+1
	AttackNum3 = 5;//攻撃3アニメーション数+1
}

CPlayer::CPlayer(float x, float y, float w, float h,int hp)
	: CPlayer()
{
	Set(x, y, w, h);

	SetHp(hp);

	Texture(GetTexture(), TEX_LEFT1, TEX_WAIT);

	mVx = VELOCITY_PLAYER;

	mLeg = PLAYER_BOTTOM;

	SetZ(GetY() - mLeg);

	mAttackPhase = EAttackPhase::Attack0;
}

CPlayer::~CPlayer()
{

}

//更新
void CPlayer::Update()
{
	switch (mState)
	{
	case EState::EWAIT:

		//処理順番を決定
		SetSortOrder(GetY() - mLeg);

		//移動入力
		Move();
		//待機アニメーション
		WaitAnimation(WaitNum);
		//アニメーションを設定
		SetAnimation();

		if (isMove == true)
		{
			mState = EState::EMOVE;
		}

		break;
	case EState::EMOVE:

		//処理順番を決定
		SetSortOrder(GetY() - mLeg);

		//移動入力
		Move();

		//移動アニメーション
		MoveAnimation(GetX(), GetY(), isMoveX, isMoveY, mVx, MoveNum);
		//アニメーションを設定
		SetAnimation();

		if (isMove == false)
		{
			mState = EState::EWAIT;
		}

		break;
	case EState::EJUMP://ジャンプ処理

		//ジャンプ開始時の座標で処理順番を更新
		SetSortOrder(mJump);

		//移動入力
		Move();
		//ジャンプアニメーション
		JumpAnimation(GetY(), mJump, JumpNum);
		//アニメーションを設定
		SetAnimation();

		//Y座標にY軸速度を加える
		SetY(GetY() + mVy);
		//Y軸速度に重力を減算する
		mVy -= GRAVITY;

		//ジャンプ距離以下にY座標がなったら
		if (GetY() - mLeg < mJump)
		{
			//状態を移動に変更
			mState = EState::EMOVE;
		}
		//ジャンプ中に画面下より下に行かないようにする
		if (GetY() - mLeg < 0)
		{
			//状態を移動に変更
			mState = EState::EMOVE;
		}
		break;

	case EState::EATTACK:	//攻撃処理
		//処理順番を決定
		SetSortOrder(GetY() - mLeg);

		Move();

		if (mAttackPhase == EAttackPhase::Attack1)
		{
			//攻撃アニメーション
			AttackAnimation(AttackNum);
		}
		else if (mAttackPhase == EAttackPhase::Attack2)
		{
			//攻撃アニメーション
			AttackAnimation(AttackNum2);
		}
		else if (mAttackPhase == EAttackPhase::Attack3)
		{
			//攻撃アニメーション
			AttackAnimation(AttackNum3);
		}

		//アニメーションを設定
		SetAnimation();


		//攻撃が終わったときネクストがtrueなら次の攻撃へ
		if (isAttack == false && isAttackNext == true)
		{
			mFrame = 0;
			isAttack = true;
			mAttackPhase = mAttackPhaseNext;
			isAttackNext = false;
		}
		//両方falseなら攻撃終了
		else if (isAttack == false && isAttackNext == false)
		{
			mFrame = 0;
			mAttackPhase = EAttackPhase::Attack0;
			mState = EState::EWAIT;
		}
		break;
	}
}

//移動入力
void CPlayer::Move()
{
	isMove = false;
	isMoveX = false;
	isMoveY = false;
	//左に移動
	if (mInput.Key('A') && mState != EState::EATTACK)
	{
		if (mVx > 0)
		{
			mVx = -mVx;
		}
		SetX(GetX() + mVx);
		isMove = true;
		isMoveX = true;
	}
	//右に移動
	if (mInput.Key('D') && mState != EState::EATTACK)
	{
		if (mVx <= 0)
		{
			mVx = -mVx;
		}
		SetX(GetX() + mVx);
		isMove = true;
		isMoveX = true;
	}
	//上に移動
	if (mInput.Key('W') && mState != EState::EATTACK)
	{
		//ステータスが移動か待機かつ足元の座標が250未満の時
		if (mState != EState::EMOVE || mState != EState::EWAIT)
		{
			if (GetY() - mLeg < 250)
			{
				SetY(GetY() + VELOCITY_PLAYER);
				SetZ(GetY() - mLeg);
				isMove = true;
				isMoveY = true;
			}
		}
		//ステータスがジャンプかつジャンプ開始時の座標が250以下の時
		if (mState == EState::EJUMP && mJump < 250)
		{
			//ジャンプ距離加算
			mJump += VELOCITY_PLAYER;
			SetY(GetY() + VELOCITY_PLAYER);
		}
	}
	//下に移動
	if (mInput.Key('S') && mState != EState::EATTACK)
	{
		//ステータスが移動か待機かつ足元の座標が0より大きい時
		if (mState == EState::EMOVE || mState == EState::EWAIT)
		{
			if (GetY() - mLeg > 0)
			{
				SetY(GetY() - VELOCITY_PLAYER);
				SetZ(GetY() - mLeg);
				isMove = true;
				isMoveY = true;
			}

		}
		//ステータスがジャンプかつジャンプ開始時の座標が0より大きい時
		if (mState == EState::EJUMP && mJump > 0)
		{
			//ジャンプ距離減算
			mJump -= VELOCITY_PLAYER;
			SetY(GetY() - VELOCITY_PLAYER);
		}
	}
	//ジャンプ
	if (mInput.Key(VK_SPACE) && mState != EState::EATTACK)
	{
		if (mState != EState::EJUMP)
		{
			//ジャンプの開始時のY座標を取得
			mJump = (GetY() - mLeg);
			//ジャンプの初速度を設定
			mVy = JUMPV0;
			//状態をジャンプに変更
			mState = EState::EJUMP;
		}
	}
	//攻撃
	if (mInput.Key(VK_LBUTTON) && mState != EState::EJUMP)
	{
		if (isClick == false)
		{
			Attack();

			if (isAttack == false && mAttackPhase == EAttackPhase::Attack0)
			{
				//攻撃段階決定
				mAttackPhase = EAttackPhase::Attack1;

				isAttack = true;
			}
			else if (isAttackNext == false && mAttackPhase != EAttackPhase::Attack3)
			{
				//攻撃段階決定
				if (mAttackPhase == EAttackPhase::Attack1)
				{
					mAttackPhaseNext = EAttackPhase::Attack2;
				}
				else if (mAttackPhase == EAttackPhase::Attack2)
				{
					mAttackPhaseNext = EAttackPhase::Attack3;
				}
				isAttackNext = true;
			}
			//攻撃に移行
			mState = EState::EATTACK;
		}
		isClick = true;
	}
	else
	{
		isClick = false;
	}
}

//攻撃コライダの生成
void CPlayer::Attack()
{
	CAttack* attack = new CAttack(this, &mX, &mY ,&mZ, mVx);
	attack->Update();
}

CPlayer::EAttackPhase CPlayer::GetAttackPhase()
{
	return mAttackPhase;
}

//死亡処理
void CPlayer::Death()
{
	//タスクリストから削除
	SetEnabled(false);
}

//アニメーションを設定
void CPlayer::SetAnimation()
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
			else if (mAnimationNum == CAnimationNumber::Move4)Texture(GetTexture(), TEX_LEFT4, TEX_MOVE);
			else if (mAnimationNum == CAnimationNumber::Move5)Texture(GetTexture(), TEX_LEFT5, TEX_MOVE);
			else                                              Texture(GetTexture(), TEX_LEFT6, TEX_MOVE);
		}
		//右移動
		else
		{
			if (mAnimationNum == CAnimationNumber::Move1)     Texture(GetTexture(), TEX_RIGHT1, TEX_MOVE);
			else if (mAnimationNum == CAnimationNumber::Move2)Texture(GetTexture(), TEX_RIGHT2, TEX_MOVE);
			else if (mAnimationNum == CAnimationNumber::Move3)Texture(GetTexture(), TEX_RIGHT3, TEX_MOVE);
			else if (mAnimationNum == CAnimationNumber::Move4)Texture(GetTexture(), TEX_RIGHT4, TEX_MOVE);
			else if (mAnimationNum == CAnimationNumber::Move5)Texture(GetTexture(), TEX_RIGHT5, TEX_MOVE);
			else                                              Texture(GetTexture(), TEX_RIGHT6, TEX_MOVE);
		}

		break;
	case EState::EJUMP://ジャンプアニメーション
		//左向き
		if (mVx < 0.0f)
		{
			if (mAnimationNum == CAnimationNumber::Move1)     Texture(GetTexture(), TEX_LEFT1, TEX_JUMP);
			else if (mAnimationNum == CAnimationNumber::Move2)Texture(GetTexture(), TEX_LEFT2, TEX_JUMP);
			else if (mAnimationNum == CAnimationNumber::Move3)Texture(GetTexture(), TEX_LEFT3, TEX_JUMP);
			else                                              Texture(GetTexture(), TEX_LEFT4, TEX_JUMP);
		}
		//右向き
		else
		{
			if (mAnimationNum == CAnimationNumber::Move1)     Texture(GetTexture(), TEX_RIGHT1, TEX_JUMP);
			else if (mAnimationNum == CAnimationNumber::Move2)Texture(GetTexture(), TEX_RIGHT2, TEX_JUMP);
			else if (mAnimationNum == CAnimationNumber::Move3)Texture(GetTexture(), TEX_RIGHT3, TEX_JUMP);
			else                                              Texture(GetTexture(), TEX_RIGHT4, TEX_JUMP);
		}
		break;
	case EState::EATTACK:	//攻撃アニメーション
		//左向き
		if (mVx < 0.0f)
		{
			if (isAttack == true)
			{
				if (mAttackPhase == EAttackPhase::Attack1)
				{
					//攻撃アニメーション
					if (mAnimationNum == CAnimationNumber::Move1)     Texture(GetTexture(), TEX_LEFT1, TEX_ATTACK1);
					else if (mAnimationNum == CAnimationNumber::Move2)Texture(GetTexture(), TEX_LEFT2, TEX_ATTACK1);
					else if (mAnimationNum == CAnimationNumber::Move3)Texture(GetTexture(), TEX_LEFT3, TEX_ATTACK1);
					else if (mAnimationNum == CAnimationNumber::Move4)Texture(GetTexture(), TEX_LEFT4, TEX_ATTACK1);
					else if (mAnimationNum == CAnimationNumber::Move5)Texture(GetTexture(), TEX_LEFT5, TEX_ATTACK1);
					else isAttack = false;
				}
				else if (mAttackPhase == EAttackPhase::Attack2)
				{
					//攻撃アニメーション
					if (mAnimationNum == CAnimationNumber::Move1)     Texture(GetTexture(), TEX_LEFT1, TEX_ATTACK2);
					else if (mAnimationNum == CAnimationNumber::Move2)Texture(GetTexture(), TEX_LEFT2, TEX_ATTACK2);
					else if (mAnimationNum == CAnimationNumber::Move3)Texture(GetTexture(), TEX_LEFT3, TEX_ATTACK2);
					else if (mAnimationNum == CAnimationNumber::Move4)Texture(GetTexture(), TEX_LEFT4, TEX_ATTACK2);
					else if (mAnimationNum == CAnimationNumber::Move5)Texture(GetTexture(), TEX_LEFT5, TEX_ATTACK2);
					else isAttack = false;
				}
				else if (mAttackPhase == EAttackPhase::Attack3)
				{
					//攻撃アニメーション
					if (mAnimationNum == CAnimationNumber::Move1)     Texture(GetTexture(), TEX_LEFT1, TEX_ATTACK3);
					else if (mAnimationNum == CAnimationNumber::Move2)Texture(GetTexture(), TEX_LEFT2, TEX_ATTACK3);
					else if (mAnimationNum == CAnimationNumber::Move3)Texture(GetTexture(), TEX_LEFT3, TEX_ATTACK3);
					else if (mAnimationNum == CAnimationNumber::Move4)Texture(GetTexture(), TEX_LEFT4, TEX_ATTACK3);
					else isAttack = false;
				}
			}
		}
		//右向き
		else
		{
			if (isAttack == true)
			{
				if (mAttackPhase == EAttackPhase::Attack1)
				{
					//攻撃アニメーション
					if (mAnimationNum == CAnimationNumber::Move1)     Texture(GetTexture(), TEX_RIGHT1, TEX_ATTACK1);
					else if (mAnimationNum == CAnimationNumber::Move2)Texture(GetTexture(), TEX_RIGHT2, TEX_ATTACK1);
					else if (mAnimationNum == CAnimationNumber::Move3)Texture(GetTexture(), TEX_RIGHT3, TEX_ATTACK1);
					else if (mAnimationNum == CAnimationNumber::Move4)Texture(GetTexture(), TEX_RIGHT4, TEX_ATTACK1);
					else if (mAnimationNum == CAnimationNumber::Move5)Texture(GetTexture(), TEX_RIGHT5, TEX_ATTACK1);
					else isAttack = false;
				}
				else if (mAttackPhase == EAttackPhase::Attack2)
				{
					//攻撃アニメーション
					if (mAnimationNum == CAnimationNumber::Move1)     Texture(GetTexture(), TEX_RIGHT1, TEX_ATTACK2);
					else if (mAnimationNum == CAnimationNumber::Move2)Texture(GetTexture(), TEX_RIGHT2, TEX_ATTACK2);
					else if (mAnimationNum == CAnimationNumber::Move3)Texture(GetTexture(), TEX_RIGHT3, TEX_ATTACK2);
					else if (mAnimationNum == CAnimationNumber::Move4)Texture(GetTexture(), TEX_RIGHT4, TEX_ATTACK2);
					else if (mAnimationNum == CAnimationNumber::Move5)Texture(GetTexture(), TEX_RIGHT5, TEX_ATTACK2);
					else isAttack = false;
				}
				else if (mAttackPhase == EAttackPhase::Attack3)
				{
					//攻撃アニメーション
					if (mAnimationNum == CAnimationNumber::Move1)     Texture(GetTexture(), TEX_RIGHT1, TEX_ATTACK3);
					else if (mAnimationNum == CAnimationNumber::Move2)Texture(GetTexture(), TEX_RIGHT2, TEX_ATTACK3);
					else if (mAnimationNum == CAnimationNumber::Move3)Texture(GetTexture(), TEX_RIGHT3, TEX_ATTACK3);
					else if (mAnimationNum == CAnimationNumber::Move4)Texture(GetTexture(), TEX_RIGHT4, TEX_ATTACK3);
					else isAttack = false;
				}

			}
		}
	}
}
