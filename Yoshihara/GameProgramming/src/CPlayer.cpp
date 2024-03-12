#include "CPlayer.h"
#include "CApplication.h"

//定数の定義
//左、右、下、上　敵テクスチャマッピング
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
		mpInstance= new CPlayer(PLAYER_STARTSET);
	}
	return mpInstance;
}

CPlayer::CPlayer()
	:CCharacter((int)CTaskPriority::Object)
	, mJump(0)
{
	mpInstance = this;
	mState = EState::EWAIT;
}

CPlayer::CPlayer(float x, float y, float w, float h)
	: CPlayer()
{
	Set(x, y, w, h);

	Texture(GetTexture(), TEX_LEFTMOVE1);

	mVx = VELOCITY_PLAYER;
}

CPlayer::~CPlayer()
{

}

void CPlayer::Update()
{
	switch (mState)
	{
	case EState::EWAIT:

		SetSortOrder(GetY() - PLAYER_BOTTOM);

		//移動入力
		Move();

		if (isMove == true)
		{
			mState = EState::EMOVE;
		}

		break;
	case EState::EMOVE:
		
		SetSortOrder(GetY() - PLAYER_BOTTOM);

		//移動入力
		Move();
		//移動アニメーション
		MoveAnimation();

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
		JumpAnimation();

		//Y座標にY軸速度を加える
		SetY(GetY() + mVy);
		//Y軸速度に重力を減算する
		mVy -= GRAVITY;

		//ジャンプ距離以下にY座標がなったら
		if (GetY() - PLAYER_BOTTOM < mJump)
		{
			//状態を移動に変更
			mState = EState::EMOVE;
		}
		//ジャンプ中に画面下より下に行かないようにする
		if (GetY() - PLAYER_BOTTOM < 0)
		{
			//状態を移動に変更
			mState = EState::EMOVE;
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
			if (GetY() - PLAYER_BOTTOM < 250)
			{
				SetY(GetY() + VELOCITY_PLAYER);
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
	if (mInput.Key('S'))
	{
		//ステータスが移動か待機かつ足元の座標が0より大きい時
		if (mState == EState::EMOVE || mState == EState::EWAIT)
		{
			if (GetY() - PLAYER_BOTTOM > 0)
			{
				SetY(GetY() - VELOCITY_PLAYER);
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
			mJump = (GetY() - PLAYER_BOTTOM);
			//ジャンプの初速度を設定
			mVy = JUMPV0;
			//状態をジャンプに変更
			mState = EState::EJUMP;
		}
	}
}

//死亡処理
void CPlayer::Death()
{
	//タスクリストから削除
	SetEnabled(false);
}


//移動アニメーション
void CPlayer::MoveAnimation()
{
	//画像を切り替える速度
	const int PITCH = 64;
	//座標を保存
	int Pos = (int)GetX();
	//Y座標だけ移動しているならY座標を入れる
	if (isMoveX == false && isMoveY == true)
	{
		Pos = (int)GetY();
	}


	//座標が0以上の時
	if (Pos >= 0)
	{
		if (Pos % PITCH < PITCH / 6)
		{
			//左移動
			if (mVx < 0.0f)
			{
				Texture(GetTexture(), TEX_LEFTMOVE6);
			}
			//右移動
			else
			{
				Texture(GetTexture(), TEX_RIGHTMOVE1);
			}
		}
		else if (Pos % PITCH < PITCH * 2 / 6)
		{
			//左移動
			if (mVx < 0.0f)
			{
				Texture(GetTexture(), TEX_LEFTMOVE5);
			}
			//右移動
			else
			{
				Texture(GetTexture(), TEX_RIGHTMOVE2);
			}
		}
		else if (Pos % PITCH < PITCH * 3 / 6)
		{
			//左移動
			if (mVx < 0.0f)
			{
				Texture(GetTexture(), TEX_LEFTMOVE4);
			}
			//右移動
			else
			{
				Texture(GetTexture(), TEX_RIGHTMOVE3);
			}
		}
		else if (Pos % PITCH < PITCH * 4 / 6)
		{
			//左移動
			if (mVx < 0.0f)
			{
				Texture(GetTexture(), TEX_LEFTMOVE3);
			}
			//右移動
			else
			{
				Texture(GetTexture(), TEX_RIGHTMOVE4);
			}
		}
		else if (Pos % PITCH < PITCH * 5 / 6)
		{
			//左移動
			if (mVx < 0.0f)
			{
				Texture(GetTexture(), TEX_LEFTMOVE2);
			}
			//右移動
			else
			{
				Texture(GetTexture(), TEX_RIGHTMOVE5);
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
				Texture(GetTexture(), TEX_RIGHTMOVE6);
			}
		}
	}
	//座標が0未満の時
	else
	{
		//正数にする
		Pos = -Pos;

		if (Pos % PITCH < PITCH / 6)
		{
			//左移動
			if (mVx < 0.0f)
			{
				Texture(GetTexture(), TEX_LEFTMOVE1);
			}
			//右移動
			else
			{
				Texture(GetTexture(), TEX_RIGHTMOVE6);
			}
		}
		else if (Pos % PITCH < PITCH * 2 / 6)
		{
			//左移動
			if (mVx < 0.0f)
			{
				Texture(GetTexture(), TEX_LEFTMOVE2);
			}
			//右移動
			else
			{
				Texture(GetTexture(), TEX_RIGHTMOVE5);
			}
		}
		else if (Pos % PITCH < PITCH * 3 / 6)
		{
			//左移動
			if (mVx < 0.0f)
			{
				Texture(GetTexture(), TEX_LEFTMOVE3);
			}
			//右移動
			else
			{
				Texture(GetTexture(), TEX_RIGHTMOVE4);
			}
		}
		else if (Pos % PITCH < PITCH * 4 / 6)
		{
			//左移動
			if (mVx < 0.0f)
			{
				Texture(GetTexture(), TEX_LEFTMOVE4);
			}
			//右移動
			else
			{
				Texture(GetTexture(), TEX_RIGHTMOVE3);
			}
		}
		else if (Pos % PITCH < PITCH * 5 / 6)
		{
			//左移動
			if (mVx < 0.0f)
			{
				Texture(GetTexture(), TEX_LEFTMOVE5);
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
				Texture(GetTexture(), TEX_LEFTMOVE6);
			}
			//右移動
			else
			{
				Texture(GetTexture(), TEX_RIGHTMOVE1);
			}
		}
	}

}

void CPlayer::JumpAnimation()
{
	//画像を切り替える速度
	const int PITCH = 256;
	//ジャンプ前とジャンプ中の座標の差を求める
	int JumpPos = GetY() - mJump;


	if (JumpPos % PITCH < PITCH / 4)
	{
		//左向き
		if (mVx < 0.0f)
		{
			Texture(GetTexture(), TEX_LEFTJUMP1);
		}
		//右向き
		else
		{
			Texture(GetTexture(), TEX_RIGHTJUMP1);
		}
	}
	else if (JumpPos % PITCH < PITCH * 2 / 4)
	{
		//左向き

		if (mVx < 0.0f)
		{
			Texture(GetTexture(), TEX_LEFTJUMP2);
		}
		//右向き
		else
		{
			Texture(GetTexture(), TEX_RIGHTJUMP2);
		}
	}
	else if (JumpPos % PITCH < PITCH * 3 / 4)
	{
		//左向き
		if (mVx < 0.0f)
		{
			Texture(GetTexture(), TEX_LEFTJUMP3);
		}
		//右向き
		else
		{
			Texture(GetTexture(), TEX_RIGHTJUMP3);
		}
	}
	else
	{
		//左向き
		if (mVx < 0.0f)
		{
			Texture(GetTexture(), TEX_LEFTJUMP4);
		}
		//右向き
		else
		{
			Texture(GetTexture(), TEX_RIGHTJUMP4);
		}
	}
}