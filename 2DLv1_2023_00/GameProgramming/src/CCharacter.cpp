#include "CCharacter.h"
#include "CApplication.h"


void CCharacter::Texture(CTexture *pTexture,
	int left, int right, int bottom, int top)
{
	mpTexture = pTexture;//�e�N�X�`���̃C���X�^���X�̃|�C���^

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



//CCharacter�̃f�t�H���g�R���X�g���N�^
CCharacter::CCharacter()

	: mpTexture(nullptr)

	, mLeft(0.0f), mRight(0.0f), mBottom(0.0f), mTop(0.0f)

	, mState(EState::EMOVE)

	, mTag(ETag::EZERO)

	, mEnabled(true)

	, mVy(0.0f)

	, mVx(0.0f)
{
	CApplication::TaskManager()->Add(this);
}

//�f�X�g���N�^
CCharacter::~CCharacter()
{
	//�^�X�N���X�g����폜
	CApplication::TaskManager()->Remove(this);
}



CTexture* CCharacter::Texture()
{
	return mpTexture;
}



void CCharacter::Move()
{
	mState = EState::EMOVE;
}



CCharacter::ETag CCharacter::Tag()
{
	return mTag;
}



bool CCharacter::Enabled()
{
	return mEnabled;
}



CCharacter::EState CCharacter::State()
{
	return mState;
}