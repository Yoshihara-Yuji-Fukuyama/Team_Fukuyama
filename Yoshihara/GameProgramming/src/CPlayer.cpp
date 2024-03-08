#include "CPlayer.h"
#include "CApplication.h"

#define PLAYER_TEXTURE "鬼＿セット.png"     //プレイヤー画像
#define PLAYER_TEXCOORD 600 ,0 ,1200 ,600	//プレイヤーテクスチャマッピング
#define VELOCITY_PLAYER 3.0f	            //プレイヤーの移動速度
#define JUMPV0 (30 / 1.4f)		            //ジャンプの初速度
#define GRAVITY (30 / 30)		            //重力加速度

//static変数の定義
CTexture CPlayer::mTexture;

//メソッドの定義
CTexture* CPlayer::GetTexture()
{
	return &mTexture;
}

CPlayer::CPlayer()
	:CCharacter((int)CTaskPriority::Object)
{
	
}

CPlayer::CPlayer(float x, float y, float w, float h)
	: CPlayer()
{
	Set(x, y, w, h);

	GetTexture()->Load(PLAYER_TEXTURE);

	Texture(GetTexture(), PLAYER_TEXCOORD);
}

CPlayer::~CPlayer()
{

}

void CPlayer::Update()
{
	//左に移動
	if (mInput.Key('A'))
	{
		SetX(GetX() - VELOCITY_PLAYER);
	}
	//右に移動
	if (mInput.Key('D'))
	{
		SetX(GetX() + VELOCITY_PLAYER);
	}
	//上に移動
	if (mInput.Key('W'))
	{
		if (GetY() - GetH() < 500)
		{
			SetY(GetY() + VELOCITY_PLAYER);
			if (mState == EState::EJUMP)
			{
				//ジャンプ距離加算
				mJump += VELOCITY_PLAYER;
			}
		}
	}
	//下に移動
	if (mInput.Key('S'))
	{
		if (GetY() - GetH() > 0)
		{
			SetY(GetY() - VELOCITY_PLAYER);
			if (mState == EState::EJUMP)
			{
				//ジャンプ距離減算
				mJump -= VELOCITY_PLAYER;
			}
		}
	}
	//ジャンプ
	if (mInput.Key(VK_SPACE))
	{
		if (mState != EState::EJUMP)
		{
			//ジャンプの開始時のY座標を取得
			mJump = (GetY() - GetH());
			//ジャンプの初速度を設定
			mVy = JUMPV0;
			//状態をジャンプに変更
			mState = EState::EJUMP;
		}
	}
	//ジャンプ処理
	if (mState == EState::EJUMP)
	{
		//Y座標にY軸速度を加える
		SetY(GetY() + mVy);
		//Y軸速度に重力を減算する
		mVy -= GRAVITY;

		//ジャンプ距離以下にY座標がなったら
		if (GetY() - GetH() < mJump)
		{
			//状態を移動に変更
			mState = EState::EMOVE;
		}

		if (GetY() - GetH() < 0)
		{
			//状態を移動に変更
			mState = EState::EMOVE;
		}
	}
}