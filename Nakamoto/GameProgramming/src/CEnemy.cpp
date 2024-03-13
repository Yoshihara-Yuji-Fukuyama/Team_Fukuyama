#include "CEnemy.h"
#include <stdio.h>	//�����Ŋm�F����p

//�萔�̒�`
#define TEX_COORD_ENEMY 0,600,1800,1200//���A�E�A���A��@�e�N�X�`���}�b�s���O
#define TEXTURE_ENEMY "Slime.png"

#define VELOCITY_SLIME 2.0f

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
}

//�G�̃R���X�g���N�^
CEnemy::CEnemy(float x, float y, float w, float h)
	: CEnemy()
{
	Set(x, y, w, h);

	mState = EState::EWAIT;

	Texture(GetTexture(), TEX_LEFTMOVE1);

	mVx = -VELOCITY_SLIME;

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

		WaitAnimation();

		break;

	case EState::EMOVE://�ړ�

		//�X���C���̑��x���ړ�
		SetX(GetX() + mVx);

		MoveAnimation();

		break;
	}

}

//�ړ��A�j���[�V����
void CEnemy::MoveAnimation()
{
	//�摜��؂�ւ��鑬�x
	const int PITCH = 64;
	//X���W��ۑ�
	int PosX = (int)GetX();


	//X���W��0�ȏ�̎�
	if ((int)GetX() >= 0)
	{
		if (PosX % PITCH < PITCH / 4)
		{
			//���ړ�
			if (mVx < 0.0f)
			{
				Texture(GetTexture(), TEX_LEFTMOVE4);
			}
			//�E�ړ�
			else
			{
				Texture(GetTexture(), TEX_RIGHTMOVE1);
			}
		}
		else if (PosX % PITCH < PITCH * 2 / 4)
		{
			//���ړ�
			if (mVx < 0.0f)
			{
				Texture(GetTexture(), TEX_LEFTMOVE3);
			}
			//�E�ړ�
			else
			{
				Texture(GetTexture(), TEX_RIGHTMOVE2);
			}
		}
		else if (PosX % PITCH < PITCH * 3 / 4)
		{
			//���ړ�
			if (mVx < 0.0f)
			{
				Texture(GetTexture(), TEX_LEFTMOVE2);
			}
			//�E�ړ�
			else
			{
				Texture(GetTexture(), TEX_RIGHTMOVE3);
			}
		}
		else
		{
			//���ړ�
			if (mVx < 0.0f)
			{
				Texture(GetTexture(), TEX_LEFTMOVE1);
			}
			//�E�ړ�
			else
			{
				Texture(GetTexture(), TEX_RIGHTMOVE4);
			}
		}
	}
	//X���W��0�����̎�
	else
	{
		//�����ɂ���
		PosX = -PosX;

		if (PosX % PITCH < PITCH / 4)
		{
			//���ړ�
			if (mVx < 0.0f)
			{
				Texture(GetTexture(), TEX_LEFTMOVE1);
			}
			//�E�ړ�
			else
			{
				Texture(GetTexture(), TEX_RIGHTMOVE4);
			}
		}
		else if (PosX % PITCH < PITCH * 2 / 4)
		{
			//���ړ�
			if (mVx < 0.0f)
			{
				Texture(GetTexture(), TEX_LEFTMOVE2);
			}
			//�E�ړ�
			else
			{
				Texture(GetTexture(), TEX_RIGHTMOVE3);
			}
		}
		else if (PosX % PITCH < PITCH * 3 / 4)
		{
			//���ړ�
			if (mVx < 0.0f)
			{
				Texture(GetTexture(), TEX_LEFTMOVE3);
			}
			//�E�ړ�
			else
			{
				Texture(GetTexture(), TEX_RIGHTMOVE2);
			}
		}
		else
		{
			//���ړ�
			if (mVx < 0.0f)
			{
				Texture(GetTexture(), TEX_LEFTMOVE4);
			}
			//�E�ړ�
			else
			{
				Texture(GetTexture(), TEX_RIGHTMOVE1);
			}
		}
	}

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

		//�Փ˂��Ă���Ƃ��͖����ɂ���
		mEnabled = false;
		printf("mEnabled��false�ɂȂ�܂���\n");

	}
}


void CEnemy::WaitAnimation()
{
	//�摜��؂�ւ��鑬�x
	const int PITCH = 64;
	mFps = 2;
	int frame = mFrame++ / mFps;

	if (frame % PITCH < PITCH / 4)
	{
		//�������ҋ@
		if (mVx < 0.0f)
		{
			Texture(GetTexture(), TEX_LEFTWAIT1);
		}
		//�E�����ҋ@
		else
		{
			Texture(GetTexture(), TEX_RIGHTWAIT1);
		}
	}
	else if (frame % PITCH < PITCH * 2 / 4)
	{
		//�������ҋ@
		if (mVx < 0.0f)
		{
			Texture(GetTexture(), TEX_LEFTWAIT2);
		}
		//�E�����ҋ@
		else
		{
			Texture(GetTexture(), TEX_RIGHTWAIT2);
		}
	}
	else if (frame % PITCH < PITCH * 3 / 4)
	{
		//�������ҋ@
		if (mVx < 0.0f)
		{
			Texture(GetTexture(), TEX_LEFTWAIT3);
		}
		//�E�����ҋ@
		else
		{
			Texture(GetTexture(), TEX_RIGHTWAIT3);
		}
	}
	else
	{
		//�������ҋ@
		if (mVx < 0.0f)
		{
			Texture(GetTexture(), TEX_LEFTWAIT4);
		}
		//�E�����ҋ@
		else
		{
			Texture(GetTexture(), TEX_RIGHTWAIT4);
		}
	}
}

