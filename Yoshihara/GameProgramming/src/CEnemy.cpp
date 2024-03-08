#include "CEnemy.h"

//�萔�̒�`
#define TEX_COORD_ENEMY 0,600,1800,1200//���A�E�A���A��@�e�N�X�`���}�b�s���O
#define TEXTURE_ENEMY "Slime.png"

//static�ϐ��̒�`
CTexture CEnemy::mTexture;

//���\�b�h�̒�`
CTexture* CEnemy::GetTexture()
{
	return &mTexture;
}

//�G�̃f�t�H���g�R���X�g���N�^
CEnemy::CEnemy()
	:CCharacter((int)CTaskPriority::Object)
{
}

//�G�̃R���X�g���N�^
CEnemy::CEnemy(float x, float y, float w, float h)
	:CEnemy()
{
	Set(x, y, w, h);

	GetTexture()->Load(TEXTURE_ENEMY);

	Texture(GetTexture(), TEX_COORD_ENEMY);
}

void CEnemy::Update()
{

}


