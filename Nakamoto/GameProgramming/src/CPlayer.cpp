#include "CPlayer.h"
#include "CApplication.h"

//左
#define LEFT_TEXCOORD 0 ,400 ,1080 ,815 //スライム待機１の座標
//右
#define RIGHT_TEXCOORD 400 ,0 ,1080 ,815 //スライム待機１の座標

#define VELOCITY_PLAYER 3.0f	//プレイヤーの移動速度

CPlayer::CPlayer()
{
	
}

CPlayer::CPlayer(float x, float y, float w, float h, CTexture* pt)
{
	Set(x, y, w, h);
	Texture(pt, RIGHT_TEXCOORD);
}

void CPlayer::Update()
{
	if (mInput.Key('A'))
	{
		float x = GetX() - VELOCITY_PLAYER;
		SetX(x);
	}

	if (mInput.Key('D'))
	{
		float x = GetX() + VELOCITY_PLAYER;
		SetX(x);
	}

	if (mInput.Key('W'))
	{
		float y = GetY() + VELOCITY_PLAYER;
		SetY(y);
	}

	if (mInput.Key('S'))
	{
		float y = GetY() - VELOCITY_PLAYER;
		SetY(y);
	}

	if (mInput.Key(VK_SPACE))
	{

	}
}