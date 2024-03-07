#include "CEnemy.h"
#include "CApplication.h"

//定数の定義
#define TEX_COORD_ENEMY 450,860,392,121//テクスチャマッピング
#define TEXTURE_ENEMY "Slime.png"


//敵のコンストラクタ
CEnemy::CEnemy(float x, float y, float w, float h)
{
	Set(x, y, w, h);

	mpTexture->Load(TEXTURE_ENEMY);

	Texture(mpTexture, TEX_COORD_ENEMY);


	//mpTexture->Load(TEXTURE_ENEMY);

	//Texture(GetTexture(), TEX_COORD_ENEMY);
}

void CEnemy::Update()
{

}


