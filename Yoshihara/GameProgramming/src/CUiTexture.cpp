#include "CUiTexture.h"

#define TEX_HP_BAR_RED 0,1799,96,0        //HP�ԐF 19:1
#define TEX_HP_BAR_YELLOW 395,1804,224,128//HP���F
#define TEX_FRAME 0,645,645,0             //�g
#define TEX_FACE 150,390,2710,2470        //��

//static�ϐ��̒�`
CTexture CUiTexture::mTextureHpBar;
CTexture CUiTexture::mTextureFrame;
CTexture CUiTexture::mTextureFace;

//static���\�b�h�̒�`
CTexture* CUiTexture::GetTextureHpBar()
{
	return &mTextureHpBar;
}

CTexture* CUiTexture::GetTextureFrame()
{
	return &mTextureFrame;
}

CTexture* CUiTexture::GetTextureFace()
{
	return &mTextureFace;
}

CUiTexture::CUiTexture()
	:CCharacter((int)CTaskPriority::UI)
{
}

CUiTexture::CUiTexture(float x, float y, float w, float h,EUiType uiType)
{
	Set(x, y, w, h);

	mUiType = uiType;

	if (mUiType == EUiType::HpRed)
	{
		Texture(GetTextureHpBar(), TEX_HP_BAR_RED);
	}
	else if (mUiType == EUiType::HpYellow)
	{
		Texture(GetTextureHpBar(), TEX_HP_BAR_YELLOW);
	}
	else if (mUiType == EUiType::Frame)
	{
		Texture(GetTextureFrame(), TEX_FRAME);
	}
	else
	{
		Texture(GetTextureFace(), TEX_FACE);
	}
}