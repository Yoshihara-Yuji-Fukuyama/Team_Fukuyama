#include "CEnemy.h"

//�萔�̒�`
#define TEX_COORD_ENEMY 0,600,1800,1200//���A�E�A���A��@�e�N�X�`���}�b�s���O
#define TEXTURE_ENEMY "Slime.png"

#define VELOCITY_SLIME 2.0f

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
	, mCollider1(this, mX, mY, 100, 100)
{
}

//�G�̃R���X�g���N�^
CEnemy::CEnemy(float x, float y, float w, float h)
	: CEnemy()
{
	Set(x, y, w, h);

	mState = EState::EMOVE;

	GetTexture()->Load(TEXTURE_ENEMY);

	Texture(GetTexture(), TEX_COORD_ENEMY);
}

void CEnemy::Collision(CCollider* m, CCollider* o)
{

}

void CEnemy::Update()
{
	//�ړ�
	if (mState== EState::EMOVE)
	{
		SetX(GetX()-VELOCITY_SLIME);
	}

}

