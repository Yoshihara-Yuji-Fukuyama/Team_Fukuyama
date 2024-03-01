#include "CPlayer2.h"
#include "CApplication.h"

#define TEXCOORD 168,188,158,128//テクスチャマッピング
#define TEXCOORD2 136,156,158,128  //右向き2
#define TEXLEFT1 188,168,158,128 //左向き１
#define TEXLEFT2 156,136,158,128 //左向き２
#define VELOCITY 4.0f //移動速度
#define GRAVITY (TIPSIZE / 20.0f) //重力加速度
#define JUMPV0 (TIPSIZE / 1.4f) //ジャンプの初速
#define  TEXCRY 196,216,158,128 //テクスチャマッピング
#define HP 3 //HPの初期値は３
#define SE_JUMP "res\\jump.wav" //ジャンプの音声ファイル

//プレイヤーの設定
CPlayer2::CPlayer2(float x, float y, float w, float h, CTexture* pt)
	:mInvincible(0)
{
	Set(x, y, w, h);

	Texture(pt, TEXCOORD);

	mTag = ETag::EPLAYER;

	sHp = HP;

	mSoundJump.Load(SE_JUMP); //ジャンプ音ロード

}



void CPlayer2::Update()
{

	//無敵時間中はカウントを減少し、泣く
	if (mInvincible > 0)
	{
		//１減算する
		mInvincible--;

		//泣く
		mState = EState::ECRY;

	}




	//Jキーでジャンプ
	if (mState != EState::EJUMP&&mInput.Key('J'))
	{
		mVy = JUMPV0;

		mState = EState::EJUMP;

		//ジャンプ音
		mSoundJump.Play();
	}



	//Aキーで左に4移動
	if (mInput.Key('A'))
	{
		mVx = -VELOCITY;

		X(X() + mVx);
	}



	//Dキーで右に4移動
	if (mInput.Key('D'))
	{
		mVx = VELOCITY;

		X(X() + mVx);
	}



	//Y座標にY軸速度を加える
	Y(Y() + mVy);

	mVy -= GRAVITY;



	//ステータスがECRYなら泣く
	if (mState == EState::ECRY)
	{
		//泣く画像を設定
		Texture(Texture(), TEXCRY);
	}


	else
	{

		const int PITCH = 32;  //画像を切り替える間隔
		

		if ((int)X() % PITCH < PITCH / 2)
		{
			if (mVx < 0.0f)//左へ移動
			{
				//左向き１を設定
				Texture(Texture(), TEXLEFT1);
			}

			else
			{
				//通常の画像を設定
				Texture(Texture(), TEXCOORD);
			}

		}


		else
		{
			if (mVx < 0.0f) //左へ移動
			{
				//左向き２を設定
				Texture(Texture(), TEXLEFT2);
			}

			else
			{
			    //2番目の画像を設定
			    Texture(Texture(), TEXCOORD2);
			}

		}

	}

}



void CPlayer2::Collision()
{
	CApplication::TaskManager()->Collision(this);
}



void CPlayer2::Collision(CCharacter* m, CCharacter* o)
{
	float x, y;
	
	switch (o->Tag())
	{
	case ETag::EENEMY:
		if (CRectangle::Collision(o, &x, &y))
		{
			//敵の衝突判定を実行
			o->Collision(o, m);

			X(X() + x); //めり込まない

			Y(Y() + y); //めり込まない

			//着地をした時
			if (y != 0.0f)
			{
				//Y軸速度を0にする
				mVy = 0.0f;

				if (y > 0.0f)
				{
					mState = EState::EMOVE;
				}


				else
				{
					//無敵時間ではないかつ敵が泣いていない
					if (mInvincible == 0 && o->State() != EState::ECRY)
					{
						//ジャンプでなければ泣く
						mState = EState::ECRY;

						mInvincible = 60;

						sHp--;
					}
				}
			}


			else
			{
				//無敵時間ではないかつ敵が泣いていない
				if (mInvincible == 0 && o->State() != EState::ECRY)
				{
					//ジャンプでなければ泣く
					mState = EState::ECRY;

					mInvincible = 60;

					sHp--;
				}
			}

		}
		break;


	case ETag::EPLAYER:

		break;


	case ETag::EBLOCK:
		if (CRectangle::Collision(o, &x, &y))
		{
			X(X() + x);
			Y(Y() + y);

			//着地したとき
			if (y != 0.0f)
			{
				//Y軸速度を0にする
				mVy = 0.0f;

				if (y > 0.0f)
				{
					mState = EState::EMOVE;
				}
			}

		}
		break;
	}

}



int CPlayer2::sHp = 0; //HP


int CPlayer2::Hp()
{
	return sHp;
}