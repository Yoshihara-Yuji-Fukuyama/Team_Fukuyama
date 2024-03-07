#include "CCharacter.h"

//テクスチャの設定
void CCharacter::Texture(CTexture* pTexture, int left, int right, int bottom, int top)
{
	mpTexture = pTexture;

	mLeft = left;

	mRight = right;

	mBottom = bottom;

	mTop = top;
}

//描画
void CCharacter::Render()
{
	mpTexture->DrawImage(
		GetX() - GetW(),
		GetX() + GetW(),
		GetY() - GetH(),
		GetY() + GetH(),
		mLeft, mRight, mBottom, mTop
	);
}

//デフォルトコンストラクタ
CCharacter::CCharacter()
	: mpTexture(nullptr)

	, mLeft(0.0f), mRight(0.0f), mBottom(0.0f), mTop(0.0f)

	, mEnabled(true)
{

}

//コンストラクタ
CCharacter::~CCharacter()
{

}

//mpTextureを返す
CTexture* CCharacter::GetTexture()
{
	return mpTexture;
}

//有効フラグを返す
bool CCharacter::GetEnabled()
{
	return mEnabled;
}