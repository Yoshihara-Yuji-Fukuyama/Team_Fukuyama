#include "CEnemy2.h"
#include "CApplication.h"

#define TEXCOORD 168, 188, 190, 160 //テクスチャマッピング
#define TEXCOORD2 136,156,190,160  //右向き2
#define TEXLEFT1 188,168,190,160 //左向き１
#define TEXLEFT2 156,136,190,160 //左向き２
#define TEXCRY 196, 216, 190, 160  //テクスチャマッピング




//敵の設定
CEnemy2::CEnemy2(float x, float y, float w, float h, CTexture* pt)

{
	Set(x, y, w, h);

	Texture(pt, TEXCOORD);

	mTag = ETag::EENEMY;

	mVx = VELOCITY;

	sNum++;  //敵の数を１増やす
}


//敵の数をゼロにする
void CEnemy2::Enemy0()
{
	sNum = 0;
}


void CEnemy2::Update()
{
	switch (mState)
	{
	case EState::ECRY:

		//泣く画像を設定
		Texture(Texture(), TEXCRY);
		
		break;

	case EState::EMOVE:

		//X軸速度分、X座標を更新する
		X(X() + mVx);

		const int PITCH = 32;  //画像を切り替える間隔

		if ((int)X() % PITCH < PITCH / 2)
		{
			if (mVx < 0.0f)
			{
				Texture(Texture(), TEXLEFT1);
			}

			else
			{
				Texture(Texture(), TEXCOORD);
			}

		}

		else
		{
			if (mVx < 0.0f)
			{
				Texture(Texture(), TEXLEFT2);
			}

			else
			{
				Texture(Texture(), TEXCOORD2);
			}
		}

		break;
	}	

	
}



void CEnemy2::Collision()
	{
			CApplication::TaskManager()->Collision(this);
    }



void CEnemy2::Collision(CCharacter* m, CCharacter* o)
{
	//めり込み調整変数を宣言する
	float x, y;

	switch (o->Tag())
	{
	case ETag::EPLAYER:

		if (CRectangle::Collision(o, &x, &y))
		{
			if (o->State() == EState::EJUMP && 
				mState != EState::ECRY)
			{

				sNum--; //敵の数を１減らす

				mState = EState::ECRY;

			}
		}
		break;

	case ETag::ETURN:
		//折り返しに当たったとき
		if (CRectangle::Collision(o, &x, &y))
		{
			//めり込まない位置まで戻す
			X(X() + x);

			Y(Y() + y);

			//X軸速度を反転させる
			mVx = -mVx;

		}
		break;
	}
}





int CEnemy2::sNum = 0;

int CEnemy2::Num()
{
	return sNum;
}