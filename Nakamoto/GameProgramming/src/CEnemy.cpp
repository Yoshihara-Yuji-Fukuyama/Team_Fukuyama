#include "CEnemy.h"

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
	, mCollider1(this, mX, mY, 100, 100)
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

}

void CEnemy::Update()
{
	//移動
	if (mState== EState::EMOVE)
	{
		SetX(GetX()-VELOCITY_SLIME);
	}

}

