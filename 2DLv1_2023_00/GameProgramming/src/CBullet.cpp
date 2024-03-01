#include "CBullet.h"
#include "CApplication.h"


//弾の動き
void CBullet::Update()
{
	//ステータスがムーブの場合動く、画面の端に行くと逆から出る
	if (mState == EState::EMOVE)
	{
		float y = Y() + H();
		if (y > 620.0f)
		{
			y = 0.0f;
		}
		Y(y);
	}
}



//当たり判定
bool CBullet::Collision(CRectangle* rect)
{
	if (CRectangle::Collision(rect))//当たった場合ストップにする
	{
		mState = EState::ESTOP;
		return true;
	}
	return false;
}



//ステータスをストップにする
CBullet::CBullet()
{
	mState = EState::ESTOP;
}



//弾の設定
CBullet::CBullet(float x, float y, float w, float h,
	float l, float r, float b, float t, CTexture* pt)
{
	Set(x, y, w, h);

	Texture(pt, l, r, b, t);

	mState = EState::EMOVE;

	mTag = ETag::EBULLET;
}



void CBullet::Collision()
{
	CApplication::CharacterManager()->Collision(this);
}


//弾の当たり判定
void CBullet::Collision(CCharacter* m, CCharacter* o)
{
	switch (o->Tag())
	{

		//他の弾に当たった場合
	case ETag::EBULLET:

		break;


		//弾以外に当たった場合
	default:

		if (CRectangle::Collision(o))
		{
			mState = EState::ESTOP;

			mEnabled = false;
		}

	}
}