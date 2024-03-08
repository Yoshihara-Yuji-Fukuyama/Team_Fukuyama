#include "CEnemy.h"

//定数の定義
#define TEX_COORD_ENEMY 0,600,1800,1200//左、右、下、上　敵テクスチャマッピング
#define TEXTURE_ENEMY "Slime.png"//スライム画像

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
{
}

//敵のコンストラクタ
CEnemy::CEnemy(float x, float y, float w, float h)
	:CEnemy()
{
	Set(x, y, w, h);

	GetTexture()->Load(TEXTURE_ENEMY);

	Texture(GetTexture(), TEX_COORD_ENEMY);
}

//デストラクタ
CEnemy::~CEnemy()
{

}

void CEnemy::Update()
{

}


