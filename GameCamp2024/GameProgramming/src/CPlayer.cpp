#include "CPlayer.h"
#include "CApplication.h"

//確認用 削除予定
#include <iostream>

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
//防御、やられ
#define TEX_MOTION 4200,3600

//スライムから受けるダメージ量
#define SLIME_TAKE_DAMAGE 10
//鬼から受けるダメージ量
#define ONI_TAKE_DAMAGE 20
//無敵時間
#define INVINCIBLE 100

#define PLAYER_STARTSET 100.0f,300.0f,300.0f,300.0f//x,y,w,h プレイヤーの初期位置

#define PLAYER_HP 100                       //プレイヤーのHP
#define VELOCITY_PLAYER 6.0f	            //プレイヤーの移動速度
#define JUMPV0 (30 / 1.4f)		            //ジャンプの初速度
#define GRAVITY (30 / 30)		            //重力加速度

#define PLAYER_BOTTOM 272                   //プレイヤー足元計算用

#define PLAYER_SHADOW_WAIT 240               //プレイヤー待機中の影計算用
#define PLAYER_SHADOW_JUMP 240               //プレイヤージャンプ中の影計算用
#define PLAYER_SHADOW_MOVE 220               //プレイヤー移動中の影計算用
#define PLAYER_SHADOW_ATTACK 240             //プレイヤー攻撃中の影計算用

#define PLAYER_SHADOW_SIZE_WAIT 250,100      //待機中の影の大きさ
#define PLAYER_SHADOW_SIZE_JUMP 250,100      //ジャンプ中の影の大きさ
#define PLAYER_SHADOW_SIZE_MOVE 350,100      //移動中の影の大きさ
#define PLAYER_SHADOW_SIZE_ATTACK 350,100    //攻撃中の影の大きさ

#define PLAYER_SHADOW_POSX 20                //影のX座標減算用

//強化の増加量
#define JUMP_POWER_AMOUNT 0.1
#define DEFENSE_POWER_AMOUNT 3
#define ATTACK_POWER_AMOUNT 5
#define ATTACK_NUM_AMOUNT 1
#define SPEED_POWER_AMOUNT 1


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
//インスタンスの削除
void CPlayer::DeleteInstance()
{
	if (mpInstance != nullptr)
	{
		delete mpInstance;
		mpInstance = nullptr;
	}
}


CPlayer::CPlayer()
	:CCharacter((int)CTaskPriority::Object)
	, mCollider(this, &mX, &mY, &mZ, 100, 200, CCollider::EColliderType::EPLAYER)
	, isClick(false)
	, mInvincible(0)
{
	isAttack = false;
	isAttackNext = false;
	isHit = false;
	isGuard = false;
	mState = EState::EWAIT;
	WaitNum = 4;//待機アニメーション数
	MoveNum = 6;//移動アニメーション数
	JumpNum = 4;//ジャンプアニメーション数
	AttackNum = 6;//攻撃1アニメーション数+1
	AttackNum2 = 6;//攻撃2アニメーション数+1
	AttackNum3 = 5;//攻撃3アニメーション数+1
	HitNum = 2;//敵の攻撃を受けた時のアニメーション数+1
	GuardNum = 1;//防御アニメーション数
	//強化系の効果
	mJumpPower = 1;
	mDeffensePower = 0;
	mAttackPower = 0;
	mAttackNumPower = 0;
	mSpeedPower = 0;
}

CPlayer::CPlayer(float x, float y, float w, float h, int hp)
	: CPlayer()
{
	Set(x, y, w, h);

	SetHp(hp);

	Texture(GetTexture(), TEX_LEFT1, TEX_WAIT);

	mVx = VELOCITY_PLAYER;

	mLeg = PLAYER_BOTTOM;

	SetZ(GetY() - mLeg);

	mAttackPhase = EAttackPhase::Attack0;
	//プレイヤーの影
	mpShadow = new CShadow(GetX() - PLAYER_SHADOW_POSX, GetShadowPosY(), PLAYER_SHADOW_SIZE_WAIT);
}

CPlayer::~CPlayer()
{

}

void CPlayer::Update()
{
	switch (mState)
	{
	case EState::EWAIT:
		//影の高さ計算用
		mShadow = PLAYER_SHADOW_WAIT;
		//影の大きさ
		mpShadow->SetShadow(GetX() - PLAYER_SHADOW_POSX, GetShadowPosY(), PLAYER_SHADOW_SIZE_WAIT);

		//処理順番を決定
		SetSortOrder(GetY() - mLeg);

		//移動入力
		Move();

		//待機アニメーション
		WaitAnimation(WaitNum);
		//アニメーションを設定
		SetAnimation();

		if (isMove == true && mState != EState::EATTACK)
		{
			mState = EState::EMOVE;
			mFrame = 0;
		}
		
		if (isHit == true && isMove == false)
		{
			mState = EState::EHIT;
			mFrame = 0;
		}

		//防御
		if (isGuard == true)
		{
			mState = EState::GUARD;
			mFrame = 0;
		}

		break;
	case EState::EMOVE:
		//影の高さ計算用
		mShadow = PLAYER_SHADOW_MOVE;
		//影の大きさ
		mpShadow->SetShadow(GetX() - PLAYER_SHADOW_POSX, GetShadowPosY(), PLAYER_SHADOW_SIZE_MOVE);

		//処理順番を決定
		SetSortOrder(GetY() - mLeg);

		//移動入力
		Move();

		//移動アニメーション
		MoveAnimation(GetX(), GetY(), isMoveX, isMoveY, mVx, MoveNum);
		//アニメーションを設定
		SetAnimation();

		if (isMove == false && mState != EState::EATTACK)
		{
			mState = EState::EWAIT;
		}
		else if (isHit == true)
		{
			mState = EState::EHIT;
			mFrame = 0;
		}

		//防御
		if (isGuard == true)
		{
			mState = EState::GUARD;
			mFrame = 0;
		}

		break;
	case EState::EJUMP://ジャンプ処理

		//影の高さ計算用
		mShadow = PLAYER_SHADOW_JUMP;
		//影の大きさ
		mpShadow->SetShadow(GetX() - PLAYER_SHADOW_POSX, GetShadowPosY(), PLAYER_SHADOW_SIZE_JUMP);

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
			//移動しているなら状態を移動に変更
			if (isMove == true)
			{
				mState = EState::EMOVE;
			}
			//していないなら状態を待機に変更
			else
			{
				mState = EState::EWAIT;
			}
		}
		//ジャンプ中に画面下より下に行かないようにする
		if (GetY() - mLeg < 0)
		{
			//移動しているなら状態を移動に変更
			if (isMove == true)
			{
				mState = EState::EMOVE;
			}
			//していないなら状態を待機に変更
			else
			{
				mState = EState::EWAIT;
			}
		}
		break;

	case EState::EATTACK:	//攻撃処理
		
		//影の高さ計算用
		mShadow = PLAYER_SHADOW_ATTACK;
		//影の大きさ
		mpShadow->SetShadow(GetX() - PLAYER_SHADOW_POSX, GetShadowPosY(), PLAYER_SHADOW_SIZE_ATTACK);

        //処理順番を決定
		SetSortOrder(GetY() - mLeg);
		//移動入力
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

		//攻撃コライダの生成 
		if (isAttack == true && isCollider == true && mAnimationNum == CAnimationNumber::Move3)
		{
			if (mAttackNumber == 1)
			{
				//攻撃1段目のコライダの生成 
				Attack();

				isCollider = false;
			}

		}
		else if (isAttack == true && isCollider1 == true && mAnimationNum == CAnimationNumber::Move3)
		{
			if (mAttackNumber == 2)
			{
				//攻撃2段目のコライダの生成 
				Attack();

				isCollider1 = false;
			}
		}
		else if (isAttack == true && isCollider2 == true && mAnimationNum == CAnimationNumber::Move3)
		{
			if (mAttackNumber == 3)
			{
				//攻撃3段目のコライダの生成 
				Attack();

				isCollider2 = false;
			}
		}
		//攻撃が終わったときネクストがtrueなら次の攻撃へ
		else if (isAttack == false && isAttackNext == true)
		{
			if (mAttackNumPower == 0)
			{
				isCollider = true;
			}
			else if (mAttackNumPower >= 2 && mAttackPhase == EAttackPhase::Attack2)
			{
				mAttackNumber = 3;
			}
			else if (mAttackNumPower >= 1 && mAttackPhase == EAttackPhase::Attack1)
			{
				mAttackNumber = 2;
			}
			else if (mAttackNumPower >= 1 && mAttackPhase == EAttackPhase::Attack2)
			{
				mAttackNumber = 1;
			}


			//攻撃コライダの生成 
			//Attack();

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

		if (isHit == true)
		{
			mState = EState::EHIT;
			mAttackPhase = EAttackPhase::Attack0;
			isAttack = false;
			isAttackNext = false;
			mFrame = 0;
		}

		break;

	case EState::EHIT:
		//影の高さ計算用
		mShadow = PLAYER_SHADOW_WAIT;
		//影の大きさ
		mpShadow->SetShadow(GetX() - PLAYER_SHADOW_POSX, GetShadowPosY(), PLAYER_SHADOW_SIZE_WAIT);

		//処理順番を決定
		SetSortOrder(GetY() - mLeg);

		HitAnimation(HitNum);

		//アニメーションを設定
		SetAnimation();

		if (isHit == false)
		{
			mState = EState::EWAIT;
		}

		break;
	case EState::GUARD:
		//影の高さ計算用
		mShadow = PLAYER_SHADOW_WAIT;
		//影の大きさ
		mpShadow->SetShadow(GetX() - PLAYER_SHADOW_POSX, GetShadowPosY(), PLAYER_SHADOW_SIZE_WAIT);

		//処理順番を決定
		SetSortOrder(GetY() - mLeg);

		//移動入力
		Move();

		GuardAnimation(GuardNum);

		//アニメーションを設定
		SetAnimation();

		if (isGuard == false)
		{
			mState = EState::EWAIT;
		}

		break;
	}

	//無敵時間
	if (mInvincible > 0)
	{
		//無敵時間中減算
		mInvincible--;
	}
}

//移動入力
void CPlayer::Move()
{
	isMove = false;
	isMoveX = false;
	isMoveY = false;
	//右に移動
	if (mInput.Key('D') && mState != EState::EATTACK && isHit == false && mState != EState::GUARD)
	{
		if (mVx <= 0)
		{
			mVx = -mVx;
		}
		SetX(GetX() + mVx);
		isMove = true;
		isMoveX = true;
	}
	//左に移動
	else if (mInput.Key('A') && mState != EState::EATTACK && isHit == false && mState != EState::GUARD)
	{
		if (mVx > 0)
		{
			mVx = -mVx;
		}
		SetX(GetX() + mVx);
		isMove = true;
		isMoveX = true;
	}
	//上に移動
	if (mInput.Key('W') && mState != EState::EATTACK && isHit == false && mState != EState::GUARD)
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
			mShadowPosY += VELOCITY_PLAYER;
			SetY(GetY() + VELOCITY_PLAYER);
		}
	}
	//下に移動
	else if (mInput.Key('S') && mState != EState::EATTACK && isHit == false && mState != EState::GUARD)
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
			mShadowPosY -= VELOCITY_PLAYER;
			SetY(GetY() - VELOCITY_PLAYER);
		}
	}
	//ジャンプ
	if (mInput.Key(VK_SPACE) && mState != EState::EATTACK && isHit == false && mState != EState::GUARD)
	{
		if (mState != EState::EJUMP)
		{
			//ジャンプの開始時のY座標を取得
			mJump = (GetY() - mLeg);
			mShadowPosY = (GetY() - mShadow);
			//ジャンプの初速度を設定
			mVy = JUMPV0 * mJumpPower;
			//状態をジャンプに変更
			mState = EState::EJUMP;
		}
	}
	//攻撃
	if (mInput.Key(VK_LBUTTON) && mState != EState::EJUMP && isHit == false && mState != EState::GUARD)
	{
		if (isClick == false)
		{
			if (isAttack == false && mAttackPhase == EAttackPhase::Attack0)
			{
				mAttackNumber = 1;
				//攻撃段階決定
				mAttackPhase = EAttackPhase::Attack1;

				isCollider = true;

				isAttack = true;
			}
			else if (isAttackNext == false && mAttackPhase != EAttackPhase::Attack3)
			{
				//攻撃段階決定
				if (mAttackPhase == EAttackPhase::Attack1)
				{
					//攻撃段階増加が1以上なら攻撃段階2へ移行
					if (mAttackNumPower >= 1)
					{
						mAttackPhaseNext = EAttackPhase::Attack2;
						isCollider1 = true;
					}
					else
					{
						mAttackPhaseNext = EAttackPhase::Attack1;
						isCollider = true;
					}
				}
				else if (mAttackPhase == EAttackPhase::Attack2)
				{
					//攻撃段階増加が2以上なら攻撃段階3へ移行
					if (mAttackNumPower >= 2)
					{
						mAttackPhaseNext = EAttackPhase::Attack3;
						isCollider2 = true;
					}
					else
					{
						mAttackPhaseNext = EAttackPhase::Attack1;
						isCollider = true;
					}
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

	//防御
	if (mInput.Key(VK_RBUTTON) && mState != EState::EATTACK)
	{
		if (isClick == false)
		{
			isGuard = true;
			mFrame = 0;
		}
	}
	else
	{
		isGuard = false;
	}
}

void CPlayer::Attack()
{
	CAttack* attack = new CAttack(this, &mX, &mY, &mZ, mVx, mAttackNumber);
	attack->Update();
}

//死亡処理
void CPlayer::Death()
{
	//タスクリストから削除
	SetEnabled(false);
}

bool CPlayer::GetMoveX()
{
	return isMoveX;
}

float CPlayer::GetmVx()
{
	return mVx;
}

void CPlayer::SetmVx()
{
	//右向きなら
	if (mVx > 0)
	{
		mVx = VELOCITY_PLAYER + mSpeedPower;
	}
	//左向きなら
	else
	{
		mVx = -(VELOCITY_PLAYER + mSpeedPower);
	}

}

//アニメーションを設定
void CPlayer::SetAnimation()
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
			else if (mAnimationNum == CAnimationNumber::Move4)Texture(GetTexture(), TEX_RIGHT4, TEX_MOVE);
			else if (mAnimationNum == CAnimationNumber::Move5)Texture(GetTexture(), TEX_RIGHT5, TEX_MOVE);
			else                                              Texture(GetTexture(), TEX_RIGHT6, TEX_MOVE);
		}
		//左移動
		else
		{
			if (mAnimationNum == CAnimationNumber::Move1)     Texture(GetTexture(), TEX_LEFT1, TEX_MOVE);
			else if (mAnimationNum == CAnimationNumber::Move2)Texture(GetTexture(), TEX_LEFT2, TEX_MOVE);
			else if (mAnimationNum == CAnimationNumber::Move3)Texture(GetTexture(), TEX_LEFT3, TEX_MOVE);
			else if (mAnimationNum == CAnimationNumber::Move4)Texture(GetTexture(), TEX_LEFT4, TEX_MOVE);
			else if (mAnimationNum == CAnimationNumber::Move5)Texture(GetTexture(), TEX_LEFT5, TEX_MOVE);
			else                                              Texture(GetTexture(), TEX_LEFT6, TEX_MOVE);
		}

		break;
	case EState::EJUMP://ジャンプアニメーション
		//右向き
		if (mVx > 0.0f)
		{
			if (mAnimationNum == CAnimationNumber::Move1)     Texture(GetTexture(), TEX_RIGHT1, TEX_JUMP);
			else if (mAnimationNum == CAnimationNumber::Move2)Texture(GetTexture(), TEX_RIGHT2, TEX_JUMP);
			else if (mAnimationNum == CAnimationNumber::Move3)Texture(GetTexture(), TEX_RIGHT3, TEX_JUMP);
			else                                              Texture(GetTexture(), TEX_RIGHT4, TEX_JUMP);
		}
		//左向き
		else
		{
			if (mAnimationNum == CAnimationNumber::Move1)     Texture(GetTexture(), TEX_LEFT1, TEX_JUMP);
			else if (mAnimationNum == CAnimationNumber::Move2)Texture(GetTexture(), TEX_LEFT2, TEX_JUMP);
			else if (mAnimationNum == CAnimationNumber::Move3)Texture(GetTexture(), TEX_LEFT3, TEX_JUMP);
			else                                              Texture(GetTexture(), TEX_LEFT4, TEX_JUMP);
		}
		break;
	case EState::EATTACK:	//攻撃アニメーション
        //右向き
		if (mVx > 0.0f)
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
		//左向き
		else
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
	case EState::EHIT:	//攻撃を受けた時のアニメーション
		if (isHit == true)
		{
			//左向き
			if (mVx < 0.0f)
			{
				if (mAnimationNum == CAnimationNumber::Move1)Texture(GetTexture(), TEX_LEFT2, TEX_MOTION);
				else isHit = false;
			}
			else
			{
				if (mAnimationNum == CAnimationNumber::Move1)Texture(GetTexture(), TEX_RIGHT2, TEX_MOTION);
				else isHit = false;
			}
		}
		break;
	case EState::GUARD:	//防御アニメーション
		if (isGuard == true)
		{
			//左向き
			if (mVx < 0.0f)
			{
				if (mAnimationNum == CAnimationNumber::Move1)Texture(GetTexture(), TEX_LEFT1, TEX_MOTION);
				else isGuard = false;
			}
			else
			{
				if (mAnimationNum == CAnimationNumber::Move1)Texture(GetTexture(), TEX_RIGHT1, TEX_MOTION);
				else isGuard = false;
			}
		}
	}
}


void CPlayer::Collision(CCollider* m, CCollider* o)
{
	float ax, ay;

	switch (o->GetCType())
	{
	case CCollider::EColliderType::ESLIME:	//スライムの体のコライダとの衝突判定

		//コライダのmとoが衝突しているか判定しているか判定
		if (CCollider::Collision(m, o, &ax, &ay))
		{
			//プレイヤーとの衝突判定を実行(めり込まない処理)
			//SetX(GetX() + ax);
			//調整中
			//SetY(GetY() + ay);


		}
		break;
	case CCollider::EColliderType::ESATTACK:	//スライムの攻撃コライダとの衝突判定
		//コライダのmとoが衝突しているか判定しているか判定
		if (CCollider::Collision(m, o, &ax, &ay))
		{
			if (mState != EState::GUARD)
			{
				if (mInvincible == 0)
				{
					//プレイヤーとの衝突判定を実行(めり込まない処理)
					//SetX(GetX() + 20);
					//調整中
					//SetY(GetY() + ay);

					mHp -= SLIME_TAKE_DAMAGE - mDeffensePower;
					mInvincible = INVINCIBLE;
					isHit = true;
				}
			}
			else if (mState == EState::GUARD)
			{
				mAttackPhase = EAttackPhase::Attack1;
			}

		}
		break;
	case CCollider::EColliderType::EONI:	//鬼の体のコライダとの衝突判定
		//コライダのmとoが衝突しているか判定しているか判定
		if (CCollider::Collision(m, o, &ax, &ay))
		{
			//プレイヤーとの衝突判定を実行(めり込まない処理)
			//SetX(GetX() + ax);
			//調整中
			//SetY(GetY() + ay);
		}
		break;
	case CCollider::EColliderType::EOATTACK:	//鬼の攻撃コライダとの衝突判定
		//コライダのmとoが衝突しているか判定しているか判定
		if (CCollider::Collision(m, o, &ax, &ay))
		{
			if (mState != EState::GUARD)
			{
				if (mInvincible == 0)
				{
					//プレイヤーとの衝突判定を実行(めり込まない処理)
					//SetX(GetX() + 20);
					//調整中
					//SetY(GetY() + ay);

					mHp -= ONI_TAKE_DAMAGE - mDeffensePower;
					mInvincible = INVINCIBLE;
					isHit = true;
				}
			}
			else if (mState == EState::GUARD)
			{
				mAttackPhase = EAttackPhase::Attack1;
			}

		}
		break;
	}
}

void CPlayer::HealHp(float heal)
{
	mHp += PLAYER_HP * heal;
	if (mHp > PLAYER_HP)
	{
		mHp = PLAYER_HP;
	}
}

float CPlayer::GetJumpPower()
{
	return mJumpPower;
}

int CPlayer::GetAttackPower()
{
	return mAttackPower;
}

//増加量の設定
void  CPlayer::SetJumpPower()
{
	mJumpPower += JUMP_POWER_AMOUNT;
}
void  CPlayer::SetDeffensePower()
{
	mDeffensePower += DEFENSE_POWER_AMOUNT;
}
void  CPlayer::SetAttackPower()
{
	mAttackPower += ATTACK_POWER_AMOUNT;
}
void  CPlayer::SetAttackNumPower()
{
	mAttackNumPower += ATTACK_NUM_AMOUNT;
}
void  CPlayer::SetSpeedPower()
{
	mSpeedPower += SPEED_POWER_AMOUNT;
}