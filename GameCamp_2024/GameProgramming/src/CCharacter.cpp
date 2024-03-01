#include "CCharacter.h"

void CCharacter::Texture(CTexture* pTexture,
	int left, int right, int bottom, int top)
{
	mpTexture = pTexture;//テクスチャのインスタンスのポインタ

	mLeft = left;

	mRight = right;

	mBottom = bottom;

	mTop = top;
}

void CCharacter::Render()
{
	mpTexture->DrawImage(
		X() - W(),
		X() + W(),
		Y() - H(),
		Y() + H(),
		mLeft, mRight, mBottom, mTop
	);
}

CCharacter::CCharacter()
	: mpTexture(nullptr)

	, mLeft(0.0f), mRight(0.0f), mBottom(0.0f), mTop(0.0f)

	, mEnabled(true)
{

}

CCharacter::~CCharacter()
{

}

CTexture* CCharacter::Texture()
{
	return mpTexture;
}

bool CCharacter::Enabled()
{
	return mEnabled;
}