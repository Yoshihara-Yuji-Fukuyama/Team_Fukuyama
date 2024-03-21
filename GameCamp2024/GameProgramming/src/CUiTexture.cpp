#include "CUiTexture.h"
#include "CPlayer.h"
#include "CUiPowerUp.h"

#define TEX_HP_BAR_RED 0,1799,96,0        //HP�ԐF 19:1
#define TEX_HP_BAR_YELLOW 394,1803,224,128//HP���F   19:1
#define TEX_FRAME 0,645,645,0             //�g
#define TEX_FACE 150,390,2710,2470        //��

#define HP_BAR_YELLOW_POSX 471            //HpYellowX���W�v�Z�p
#define HP_BAR_RED_POSX 520               //HpRedX���W�v�Z�p
#define HP_BAR_POSY 945                   //HpY���W�v�Z�p
#define FACE_POSX 830                     //FaceX���W�v�Z�p
#define FACE_POSY 985                     //FaceY���W�v�Z�p
#define FRAME_POSX 830                    //FrameX���W�v�Z�p
#define FRAME_POSY 990                    //FrameY���W�v�Z�p
#define ITEM_POSX 830          //�ŏ��̃A�C�e����X���W
#define ITEM_POSX_DISTANCE 50 //X���W�̍�
#define ITEM_POSY 900          //�ŏ��̃A�C�e����Y���W

//static�ϐ��̒�`
CTexture CUiTexture::mTextureHpBar;
CTexture CUiTexture::mTextureFrame;
CTexture CUiTexture::mTextureFace;

int CUiTexture::mItemNum;

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

void CUiTexture::SetItemNum()
{
	mItemNum = 0;
}

CUiTexture::CUiTexture()
	:CCharacter((int)CTaskPriority::UI)
{
}

CUiTexture::CUiTexture(float w, float h, EUiType uiType, int left, int right, int bottom, int top)
	: CUiTexture()
{
	SetW(w);
	SetH(h);
	mW = w;
	//����ۑ�
	mItemNumSave = mItemNum;

	mUiType = uiType;
	//HP�̍ő�l��ݒ�
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
	else if (mUiType == EUiType::HpRed)
	{
		Texture(GetTextureHpBar(), TEX_HP_BAR_RED);
	}
	else if (mUiType == EUiType::Item)
	{
		Texture(CUiPowerUp::GetTexture(), left, right, bottom, top);
		mItemNum++;
	}

}

//�X�V
void CUiTexture::Update()
{
	//���݂�HP��ݒ�
	mHp = CPlayer::GetInstance()->GetHp();

	//HP�̊������v�Z
	float mHpPar = mHp/mMaxHp;

	//�g
	if (mUiType == EUiType::Frame)
	{
		Set(CPlayer::GetInstance()->GetX() - FRAME_POSX, FRAME_POSY, GetW(), GetH());
	}
	//��\��
	else if (mUiType == EUiType::Face)
	{
		Set(CPlayer::GetInstance()->GetX() - FACE_POSX, FACE_POSY, GetW(), GetH());
	}
	//����HP
	else if (mUiType == EUiType::HpYellow)
	{
		//����HP�̊��������炷
		SetW(mW * mHpPar);
		//X���W�͍ŏ��ƕύX��̕��̍��������Čv�Z����
		Set(CPlayer::GetInstance()->GetX() - HP_BAR_YELLOW_POSX - (mW - GetW()), HP_BAR_POSY, GetW(), GetH());
	}
	//HP�ő�l
	else if (mUiType == EUiType::HpRed)
	{
		Set(CPlayer::GetInstance()->GetX() - HP_BAR_RED_POSX, HP_BAR_POSY, GetW(), GetH());
	}
	//�A�C�e��
	else if (mUiType == EUiType::Item)
	{
		Set(CPlayer::GetInstance()->GetX() - ITEM_POSX + ITEM_POSX_DISTANCE * mItemNumSave, ITEM_POSY, GetW(), GetH());
	}
}