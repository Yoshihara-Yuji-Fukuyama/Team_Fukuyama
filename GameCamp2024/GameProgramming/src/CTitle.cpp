#include "CTitle.h"
//テクスチャマッピング
#define TEX_TITLE 0,1920,1080,0 
#define TEX_TITLE_NAME 0,718,509,0
#define TEX_RESULT 0,1920,1080,0

//static変数の宣言
CTexture CTitle::mTextureTitle;
CTexture CTitle::mTextureTitleName;
CTexture CTitle::mTextureResult;


CTexture* CTitle::GetTextureTitle()
{
	return &mTextureTitle;
}
CTexture* CTitle::GetTextureTitleName()
{
	return &mTextureTitleName;
}
CTexture* CTitle::GetTextureResult()
{
	return &mTextureResult;
}

//デフォルトコンストラクタ
CTitle::CTitle()
	:CCharacter((int)CTaskPriority::Title)
{

}
//コンストラクタ
CTitle::CTitle(float x, float y, float w, float h, CTexture* texture)
	:CTitle()
{
	Set(x, y, w, h);

	//テクスチャがタイトルなら
	if (texture == GetTextureTitle())
	{
		Texture(texture, TEX_TITLE);
	}
	else if (texture == GetTextureTitleName())
	{
		Texture(texture, TEX_TITLE_NAME);
	}
	else
	{
		Texture(texture, TEX_RESULT);
	}
	
}