#include "CEnemy.h"

//�萔�̒�`
//���A�E�A���A��@�G�e�N�X�`���}�b�s���O
//�ړ�
#define TEX_LEFTMOVE1 0,600,1200,600
#define TEX_LEFTMOVE2 600,1200,1200,600
#define TEX_LEFTMOVE3 1200,1800,1200,600
#define TEX_LEFTMOVE4 1800,2400,1200,600
#define TEX_RIGHTMOVE1 600,0,1200,600
#define TEX_RIGHTMOVE2 1200,600,1200,600
#define TEX_RIGHTMOVE3 1800,1200,1200,600
#define TEX_RIGHTMOVE4 2400,1800,1200,600
//�ҋ@
#define TEX_LEFTWAIT1 0,600,1800,1200
#define TEX_LEFTWAIT2 600,1200,1800,1200
#define TEX_LEFTWAIT3 1200,1800,1800,1200
#define TEX_LEFTWAIT4 1800,2400,1800,1200
#define TEX_RIGHTWAIT1 600,0,1800,1200
#define TEX_RIGHTWAIT2 1200,600,1800,1200
#define TEX_RIGHTWAIT3 1800,1200,1800,1200
#define TEX_RIGHTWAIT4 2400,1800,1800,1200

#define SLIME_BOTTOM 130                    //�X���C�������v�Z�p
#define VELOCITY_SLIME 2.0f                 //�X���C���̈ړ����x

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
	, mColider(this, &mX, &mY, 140, 90)
{
	WaitNum = 4;//�ҋ@�A�j���[�V������
	MoveNum = 4;//�ړ��A�j���[�V������
	AttackNum = 4;//�U���A�j���[�V������
}

//�G�̃R���X�g���N�^
CEnemy::CEnemy(float x, float y, float w, float h)
	:CEnemy()
{
	Set(x, y, w, h);

	mState = EState::EWAIT;

	Texture(GetTexture(), TEX_LEFTMOVE1);

	mVx = -VELOCITY_SLIME;

}


void CEnemy::Collision(CCollider* m, CCollider* o)
{
	float ax, ay;
	//�R���C�_��m��o���Փ˂��Ă��邩���肵�Ă��邩����
	if (CCollider::Collision(m, o, &ax, &ay))
	{
		//�v���C���[�Ƃ̏Փ˔�������s(�߂荞�܂Ȃ�����)
		SetX(GetX() + ax);
		SetY(GetY() + ay);
	}
}

//�f�X�g���N�^
CEnemy::~CEnemy()
{

}

void CEnemy::Death()
{
	//�^�X�N���X�g����폜
	SetEnabled(false);
}

void CEnemy::Update()
{
	//�������Ԃ�����
	SetSortOrder(GetY() - SLIME_BOTTOM);
	switch (mState)
	{
	case EState::EWAIT://�ҋ@

		//�ҋ@�A�j���[�V����
		AnimSetNum = WaitAnimation(WaitNum);
		//�A�j���[�V������ݒ�
		SetAnimation();

		break;
		
	case EState::EMOVE://�ړ�

		//�X���C���̑��x���ړ�
		SetX(GetX() + mVx);
		isMoveX = true;

		//�ړ��A�j���[�V����
		AnimSetNum = MoveAnimation(GetX(), GetY(), isMoveX, isMoveY, mVx, MoveNum);
		//�A�j���[�V������ݒ�
		SetAnimation();

		break;
	}

}

//�A�j���[�V������ݒ�
void CEnemy::SetAnimation()
{
	switch (mState)
	{
	case EState::EWAIT:
		//������
		if (mVx < 0.0f)
		{
			if (AnimSetNum == 1)     Texture(GetTexture(), TEX_LEFTWAIT1);
			else if (AnimSetNum == 2)Texture(GetTexture(), TEX_LEFTWAIT2);
			else if (AnimSetNum == 3)Texture(GetTexture(), TEX_LEFTWAIT3);
			else                     Texture(GetTexture(), TEX_LEFTWAIT4);
		}
		//�E����
		else
		{
			if (AnimSetNum == 1)     Texture(GetTexture(), TEX_RIGHTWAIT1);
			else if (AnimSetNum == 2)Texture(GetTexture(), TEX_RIGHTWAIT2);
			else if (AnimSetNum == 3)Texture(GetTexture(), TEX_RIGHTWAIT3);
			else                     Texture(GetTexture(), TEX_RIGHTWAIT4);
		}

		break;
	case EState::EMOVE:
		//���ړ�
		if (mVx < 0.0f)
		{
			if (AnimSetNum == 1)     Texture(GetTexture(), TEX_LEFTMOVE1);
			else if (AnimSetNum == 2)Texture(GetTexture(), TEX_LEFTMOVE2);
			else if (AnimSetNum == 3)Texture(GetTexture(), TEX_LEFTMOVE3);
			else                     Texture(GetTexture(), TEX_LEFTMOVE4);
		}
		//�E�ړ�
		else
		{
			if (AnimSetNum == 1)     Texture(GetTexture(), TEX_RIGHTMOVE1);
			else if (AnimSetNum == 2)Texture(GetTexture(), TEX_RIGHTMOVE2);
			else if (AnimSetNum == 3)Texture(GetTexture(), TEX_RIGHTMOVE3);
			else                     Texture(GetTexture(), TEX_RIGHTMOVE4);
		}

		break;
	}
}


