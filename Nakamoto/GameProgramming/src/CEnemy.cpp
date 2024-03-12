#include "CEnemy.h"
#include <stdio.h>	//文字で確認する用

//定数の定義
#define TEX_COORD_ENEMY 0,600,1800,1200//左、右、下、上　テクスチャマッピング
#define TEXTURE_ENEMY "Slime.png"

#define VELOCITY_SLIME 2.0f

//static変数の定義
CTexture CEnemy::mTexture;

//メソッドの定義
CTexture* CEnemy::GetTexture()
{
	return &mTexture;
}

//敵のデフォルトコンストラクタ
CEnemy::CEnemy()
	:CCharacter((int)CTaskPriority::Object)
	, mColider(this, &mX, &mY, 140, 90)
{
}

//敵のコンストラクタ
CEnemy::CEnemy(float x, float y, float w, float h)
	: CEnemy()
{
	Set(x, y, w, h);

	mState = EState::EMOVE;

	GetTexture()->Load(TEXTURE_ENEMY);

	Texture(GetTexture(), TEX_COORD_ENEMY);
}

void CEnemy::Collision(CCollider* m, CCollider* o)
{
	float ax, ay;
	//コライダのmとoが衝突しているか判定しているか判定
	if (CCollider::Collision(m, o,&ax,&ay))
	{
		//プレイヤーとの衝突判定を実行(めり込まない処理)
		SetX(GetX() + ax);
		SetY(GetY() + ay);

		//衝突しているときは無効にする
		mEnabled = false;
		printf("mEnabledがfalseになりました\n");

	}
}

void CEnemy::Update()
{
	//移動
	if (mState== EState::EMOVE)
	{
		SetX(GetX()-VELOCITY_SLIME);
	}

}