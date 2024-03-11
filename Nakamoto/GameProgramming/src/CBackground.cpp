#include "CBackground.h"

//定数の定義
#define TEX_COORD_BACKGROUND 0,1920,1080,0//テクスチャマッピング
#define TEXTURE_BACKGROUND "Background.png"

//static変数の定義
CTexture CBackground::mTexture;

//メソッドの定義
CTexture* CBackground::GetTexture()
{
	return &mTexture;
}

//背景のデフォルトコンストラクタ
CBackground::CBackground()
	:CCharacter((int)CTaskPriority::Field)
{

}
//背景のコンストラクタ
CBackground::CBackground(float x, float y, float w, float h)
	:CBackground()
{
	Set(x, y, w, h);

	GetTexture()->Load(TEXTURE_BACKGROUND);

	Texture(GetTexture(), TEX_COORD_BACKGROUND);
}

void CBackground::Update()
{
}
