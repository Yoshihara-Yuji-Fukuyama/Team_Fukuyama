#include "CUiTexture.h"
#include "CPlayer.h"

#define TEX_HP_BAR_RED 0,1799,96,0        //HP赤色 19:1
#define TEX_HP_BAR_YELLOW 394,1803,224,128//HP黄色   19:1
#define TEX_FRAME 0,645,645,0             //枠
#define TEX_FACE 150,390,2710,2470        //顔

#define HP_BAR_YELLOW_POSX 471            //HpYellowX座標計算用
#define HP_BAR_RED_POSX 520               //HpRedX座標計算用
#define HP_BAR_POSY 945                   //HpY座標計算用
#define FACE_POSX 830                     //FaceX座標計算用
#define FACE_POSY 985                     //FaceY座標計算用
#define FRAME_POSX 830                    //FrameX座標計算用
#define FRAME_POSY 990                    //FrameY座標計算用

//static変数の定義
CTexture CUiTexture::mTextureHpBar;
CTexture CUiTexture::mTextureFrame;
CTexture CUiTexture::mTextureFace;

//staticメソッドの定義
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

CUiTexture::CUiTexture(float w, float h, EUiType uiType)
	: CUiTexture()
{
	SetW(w);
	SetH(h);
	mW = w;

	mUiType = uiType;
	//HPの最大値を設定
	mMaxHp = CPlayer::GetInstance()->GetHp();

	if (mUiType == EUiType::Face)
	{
		Texture(GetTextureFace(), TEX_FACE);
	}
	else if (mUiType == EUiType::Frame)
	{
		Texture(GetTextureFrame(), TEX_FRAME);
	}
	else if (mUiType == EUiType::HpYellow)
	{
		Texture(GetTextureHpBar(), TEX_HP_BAR_YELLOW);
	}
	else
	{
		Texture(GetTextureHpBar(), TEX_HP_BAR_RED);
	}

}

//更新
void CUiTexture::Update()
{
	//現在のHPを設定
	mHp = CPlayer::GetInstance()->GetHp();

	//HPの割合を計算
	float mHpPar = mHp/mMaxHp;

	//枠
	if (mUiType == EUiType::Frame)
	{
		Set(CPlayer::GetInstance()->GetX() - FRAME_POSX, FRAME_POSY, GetW(), GetH());
	}
	//顔表示
	else if (mUiType == EUiType::Face)
	{
		Set(CPlayer::GetInstance()->GetX() - FACE_POSX, FACE_POSY, GetW(), GetH());
	}
	//現在HP
	else if (mUiType == EUiType::HpYellow)
	{
		//幅をHPの割合分減らす
		SetW(mW * mHpPar);
		//X座標は最初と変更後の幅の差を引いて計算する
		Set(CPlayer::GetInstance()->GetX() - HP_BAR_YELLOW_POSX - (mW - GetW()), HP_BAR_POSY, GetW(), GetH());
	}
	//HP最大値
	else
	{
		Set(CPlayer::GetInstance()->GetX() - HP_BAR_RED_POSX, HP_BAR_POSY, GetW(), GetH());
	}
	
}
