#include "CBackground.h"

//�萔�̒�`
#define TEX_COORD_BACKGROUND 0,1920,1080,0//�e�N�X�`���}�b�s���O
#define TEXTURE_BACKGROUND "Background.png"

//static�ϐ��̒�`
CTexture CBackground::mTexture;

//���\�b�h�̒�`
CTexture* CBackground::GetTexture()
{
	return &mTexture;
}

//�w�i�̃f�t�H���g�R���X�g���N�^
CBackground::CBackground()
	:CCharacter((int)CTaskPriority::Field)
{

}
//�w�i�̃R���X�g���N�^
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
