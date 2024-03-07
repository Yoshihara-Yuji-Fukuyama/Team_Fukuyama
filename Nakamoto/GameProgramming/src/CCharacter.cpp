#include "CCharacter.h"

//�e�N�X�`���̐ݒ�
void CCharacter::Texture(CTexture* pTexture, int left, int right, int bottom, int top)
{
	mpTexture = pTexture;

	mLeft = left;

	mRight = right;

	mBottom = bottom;

	mTop = top;
}

//�`��
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

//�f�t�H���g�R���X�g���N�^
CCharacter::CCharacter()
	: mpTexture(nullptr)

	, mLeft(0.0f), mRight(0.0f), mBottom(0.0f), mTop(0.0f)

	, mEnabled(true)
{

}

//�R���X�g���N�^
CCharacter::~CCharacter()
{

}

//mpTexture��Ԃ�
CTexture* CCharacter::GetTexture()
{
	return mpTexture;
}

//�L���t���O��Ԃ�
bool CCharacter::GetEnabled()
{
	return mEnabled;
}