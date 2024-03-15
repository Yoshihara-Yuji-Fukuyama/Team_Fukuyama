#include "CPlayer.h"
#include "CApplication.h"
#include "CCollisionManager.h"

//定数の定義
//左、右、下、上　敵テクスチャマッピング
//待機
#define TEX_LEFTWAIT1 600,0,3000,2400
#define TEX_LEFTWAIT2 1200,600,3000,2400
#define TEX_LEFTWAIT3 1800,1200,3000,2400
#define TEX_LEFTWAIT4 2400,1800,3000,2400
#define TEX_RIGHTWAIT1 0,600,3000,2400
#define TEX_RIGHTWAIT2 600,1200,3000,2400
#define TEX_RIGHTWAIT3 1200,1800,3000,2400
#define TEX_RIGHTWAIT4 1800,2400,3000,2400
//移動
#define TEX_LEFTMOVE1 600,0,2400,1800
#define TEX_LEFTMOVE2 1200,600,2400,1800
#define TEX_LEFTMOVE3 1800,1200,2400,1800
#define TEX_LEFTMOVE4 2400,1800,2400,1800
#define TEX_LEFTMOVE5 3000,2400,2400,1800
#define TEX_LEFTMOVE6 3600,3000,2400,1800
#define TEX_RIGHTMOVE1 0, 600, 2400, 1800
#define TEX_RIGHTMOVE2 600, 1200, 2400, 1800
#define TEX_RIGHTMOVE3 1200, 1800, 2400, 1800
#define TEX_RIGHTMOVE4 1800, 2400, 2400, 1800
#define TEX_RIGHTMOVE5 2400, 3000, 2400, 1800
#define TEX_RIGHTMOVE6 3000, 3600, 2400, 1800
//ジャンプ
#define TEX_LEFTJUMP1 600,0,3600,3000
#define TEX_LEFTJUMP2 1200,600,3600,3000
#define TEX_LEFTJUMP3 1800,1200,3600,3000
#define TEX_LEFTJUMP4 2400,1800,3600,3000
#define TEX_RIGHTJUMP1 0,600,3600,3000
#define TEX_RIGHTJUMP2 600,1200,3600,3000
#define TEX_RIGHTJUMP3 1200,1800,3600,3000
#define TEX_RIGHTJUMP4 1800,2400,3600,3000

//攻撃1
#define TEX_LEFTATTACK1_1 600,0,600,0
#define TEX_LEFTATTACK2_1 1200,600,600,0
#define TEX_LEFTATTACK3_1 1800,1200,600,0
#define TEX_LEFTATTACK4_1 2400,1800,600,0
#define TEX_LEFTATTACK5_1 3000,2400,600,0
#define TEX_RIGHTATTACK1_1  0,600,600,0
#define TEX_RIGHTATTACK2_1  600,1200,600,0
#define TEX_RIGHTATTACK3_1  1200,1800,600,0
#define TEX_RIGHTATTACK4_1  1800,2400,600,0
#define TEX_RIGHTATTACK5_1  2400,3000,600,0


#define PLAYER_STARTSET 100.0f,300.0f,300.0f,300.0f//x,y,w,h プレイヤーの初期位置

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
		mpInstance = new CPlayer(PLAYER_STARTSET);
	}
	return mpInstance;
}

CPlayer::CPlayer()
	:CCharacter((int)CTaskPriority::Object)
	, mCollider(this, &mX, &mY, &mZ,100, 100)
{
	mState = EState::EWAIT;
	WaitNum = 4;//待機アニメーション数
	MoveNum = 6;//移動アニメーション数
	JumpNum = 4;//ジャンプアニメーション数
	AttackNum = 6;//攻撃アニメーション数
}

CPlayer::CPlayer(float x, float y, float w, float h)
	: CPlayer()
{
	Set(x, y, w, h);

	Texture(GetTexture(), TEX_LEFTMOVE1);

	mVx = VELOCITY_PLAYER;

	mLeg = PLAYER_BOTTOM;

	SetZ(GetY() - mLeg);
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

		Attack();
		//攻撃アニメーション
		AttackAnimation(AttackNum);
		//アニメーションを設定
		SetAnimation();

		if (isAttack == false)
		{
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
	if (mInput.Key('A'))
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
	if (mInput.Key('D'))
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
	if (mInput.Key('W'))
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

			//攻撃
			if (mInput.Key(VK_LBUTTON) && mState != EState::EJUMP)
			{
				mState = EState::EATTACK;
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
	if (mInput.Key('S'))
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
	if (mInput.Key(VK_SPACE))
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
		mState = EState::EATTACK;
		isAttack = true;
	}

}

void CPlayer::Attack()
{
	CAttack* attack = new CAttack(this, &mX, &mY);
	//attack->Set(GetX(), GetY(), 30, 100);
	//CCollisionManager::GetInstance()->Add(attack);
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
			if (mAnimationNum == CAnimationNumber::Move1)     Texture(GetTexture(), TEX_LEFTWAIT1);
			else if (mAnimationNum == CAnimationNumber::Move2)Texture(GetTexture(), TEX_LEFTWAIT2);
			else if (mAnimationNum == CAnimationNumber::Move3)Texture(GetTexture(), TEX_LEFTWAIT3);
			else											  Texture(GetTexture(), TEX_LEFTWAIT4);
		}
		//右向き
		else
		{
			if (mAnimationNum == CAnimationNumber::Move1)     Texture(GetTexture(), TEX_RIGHTWAIT1);
			else if (mAnimationNum == CAnimationNumber::Move2)Texture(GetTexture(), TEX_RIGHTWAIT2);
			else if (mAnimationNum == CAnimationNumber::Move3)Texture(GetTexture(), TEX_RIGHTWAIT3);
			else											  Texture(GetTexture(), TEX_RIGHTWAIT4);
		}
		break;
	case EState::EMOVE://移動アニメーション
		//左移動
		if (mVx < 0.0f)
		{
			if (mAnimationNum == CAnimationNumber::Move1)     Texture(GetTexture(), TEX_LEFTMOVE1);
			else if (mAnimationNum == CAnimationNumber::Move2)Texture(GetTexture(), TEX_LEFTMOVE2);
			else if (mAnimationNum == CAnimationNumber::Move3)Texture(GetTexture(), TEX_LEFTMOVE3);
			else if (mAnimationNum == CAnimationNumber::Move4)Texture(GetTexture(), TEX_LEFTMOVE4);
			else if (mAnimationNum == CAnimationNumber::Move5)Texture(GetTexture(), TEX_LEFTMOVE5);
			else                                              Texture(GetTexture(), TEX_LEFTMOVE6);
		}
		//右移動
		else
		{
			if (mAnimationNum == CAnimationNumber::Move1)     Texture(GetTexture(), TEX_RIGHTMOVE1);
			else if (mAnimationNum == CAnimationNumber::Move2)Texture(GetTexture(), TEX_RIGHTMOVE2);
			else if (mAnimationNum == CAnimationNumber::Move3)Texture(GetTexture(), TEX_RIGHTMOVE3);
			else if (mAnimationNum == CAnimationNumber::Move4)Texture(GetTexture(), TEX_RIGHTMOVE4);
			else if (mAnimationNum == CAnimationNumber::Move5)Texture(GetTexture(), TEX_RIGHTMOVE5);
			else											  Texture(GetTexture(), TEX_RIGHTMOVE6);
		}

		break;
	case EState::EJUMP://ジャンプアニメーション
		//左向き
		if (mVx < 0.0f)
		{
			if (mAnimationNum == CAnimationNumber::Move1)     Texture(GetTexture(), TEX_LEFTJUMP1);
			else if (mAnimationNum == CAnimationNumber::Move2)Texture(GetTexture(), TEX_LEFTJUMP2);
			else if (mAnimationNum == CAnimationNumber::Move3)Texture(GetTexture(), TEX_LEFTJUMP3);
			else                                              Texture(GetTexture(), TEX_LEFTJUMP4);
		}
		//右向き
		else
		{
			if (mAnimationNum == CAnimationNumber::Move1)     Texture(GetTexture(), TEX_RIGHTJUMP1);
			else if (mAnimationNum == CAnimationNumber::Move2)Texture(GetTexture(), TEX_RIGHTJUMP2);
			else if (mAnimationNum == CAnimationNumber::Move3)Texture(GetTexture(), TEX_RIGHTJUMP3);
			else                                              Texture(GetTexture(), TEX_RIGHTJUMP4);
		}
		break;

	case EState::EATTACK:	//攻撃アニメーション
		//左移動
		if (mVx < 0.0f)
		{
			if (isAttack == true)
			{
				if (mAnimationNum == CAnimationNumber::Move1)     Texture(GetTexture(), TEX_LEFTATTACK1_1);
				else if (mAnimationNum == CAnimationNumber::Move2)Texture(GetTexture(), TEX_LEFTATTACK2_1);
				else if (mAnimationNum == CAnimationNumber::Move3)Texture(GetTexture(), TEX_LEFTATTACK3_1);
				else if (mAnimationNum == CAnimationNumber::Move4)Texture(GetTexture(), TEX_LEFTATTACK4_1);
				else if (mAnimationNum == CAnimationNumber::Move5)Texture(GetTexture(), TEX_LEFTATTACK5_1);
				else isAttack = false;
			}
		}
			
		//右移動
		else
		{
			if (isAttack == true)
			{
				if (mAnimationNum == CAnimationNumber::Move1)     Texture(GetTexture(), TEX_RIGHTATTACK1_1);
				else if (mAnimationNum == CAnimationNumber::Move2)Texture(GetTexture(), TEX_RIGHTATTACK2_1);
				else if (mAnimationNum == CAnimationNumber::Move3)Texture(GetTexture(), TEX_RIGHTATTACK3_1);
				else if (mAnimationNum == CAnimationNumber::Move4)Texture(GetTexture(), TEX_RIGHTATTACK4_1);
				else if (mAnimationNum == CAnimationNumber::Move5)Texture(GetTexture(), TEX_RIGHTATTACK5_1);
				else isAttack = false;
			}
		}
	}
}
