#include "CPlayer.h"
#include "CApplication.h"

//�萔�̒�`
//���A�E�A���A��@�G�e�N�X�`���}�b�s���O
//�ړ�
#define TEX_LEFTMOVE1 600,0,2400,1800
#define TEX_LEFTMOVE2 1200,600,2400,1800
#define TEX_LEFTMOVE3 1800,1200,2400,1800
#define TEX_LEFTMOVE4 2400,1800,2400,1800
#define TEX_LEFTMOVE5 3000,2400,2400,1800
#define TEX_LEFTMOVE6 3600,3000,2400,1800
#define TEX_RIGHTMOVE1 0, 600, 2400, 1800
#define TEX_RIGHTMOVE2 600, 1200, 2400, 1800
#define TEX_RIGHTMOVE3 1200, 1800, 2400, 1800
#define TEX_RIGHTMOVE4 1800, 2400, 2400, 1800
#define TEX_RIGHTMOVE5 2400, 3000, 2400, 1800
#define TEX_RIGHTMOVE6 3000, 3600, 2400, 1800







#define PLAYER_STARTSET 100.0f,300.0f,300.0f,300.0f//x,y,w,h �v���C���[�̏����ʒu

#define VELOCITY_PLAYER 3.0f	            //�v���C���[�̈ړ����x
#define JUMPV0 (30 / 1.4f)		            //�W�����v�̏����x
#define GRAVITY (30 / 30)		            //�d�͉����x
#define PLAYER_BOTTOM 270                   //�v���C���[�����v�Z�p

//static�ϐ��̒�`
CTexture CPlayer::mTexture;

CPlayer* CPlayer::mpInstance;

//���\�b�h�̒�`
CTexture* CPlayer::GetTexture()
{
	return &mTexture;
}

//�C���X�^���X�̎擾
CPlayer* CPlayer::GetInstance()
{
	if (mpInstance == nullptr)
	{
		mpInstance= new CPlayer(PLAYER_STARTSET);
	}
	return mpInstance;
}

CPlayer::CPlayer()
	:CCharacter((int)CTaskPriority::Object)
	, mJump(0)
{
	mpInstance = this;
	mState = EState::EWAIT;
}

CPlayer::CPlayer(float x, float y, float w, float h)
	: CPlayer()
{
	Set(x, y, w, h);

	Texture(GetTexture(), TEX_LEFTMOVE1);

	mVx = VELOCITY_PLAYER;
}

CPlayer::~CPlayer()
{

}

void CPlayer::Update()
{
	switch (mState)
	{
	case EState::EWAIT:

		SetSortOrder(GetY() - PLAYER_BOTTOM);

		//�ړ�����
		Move();

		if (isMove == true)
		{
			mState = EState::EMOVE;
		}

		break;
	case EState::EMOVE:
		
		SetSortOrder(GetY() - PLAYER_BOTTOM);

		//�ړ�����
		Move();
		//�ړ��A�j���[�V����
		MoveAnimation();

		if (isMove == false)
		{
			mState = EState::EWAIT;
		}

		break;
	case EState::EJUMP://�W�����v����

		//�W�����v�J�n���̍��W�ŏ������Ԃ��X�V
		SetSortOrder(mJump);

		//�ړ�����
		Move();

		//Y���W��Y�����x��������
		SetY(GetY() + mVy);
		//Y�����x�ɏd�͂����Z����
		mVy -= GRAVITY;

		//�W�����v�����ȉ���Y���W���Ȃ�����
		if (GetY() - PLAYER_BOTTOM < mJump)
		{
			//��Ԃ��ړ��ɕύX
			mState = EState::EMOVE;
		}
		//�W�����v���ɉ�ʉ���艺�ɍs���Ȃ��悤�ɂ���
		if (GetY() - PLAYER_BOTTOM < 0)
		{
			//��Ԃ��ړ��ɕύX
			mState = EState::EMOVE;
		}
		break;
	}


}

//�ړ�����
void CPlayer::Move()
{
	isMove = false;
	//���Ɉړ�
	if (mInput.Key('A'))
	{
		if (mVx > 0)
		{
			mVx = -mVx;
		}
		SetX(GetX() + mVx);
		isMove = true;
	}
	//�E�Ɉړ�
	if (mInput.Key('D'))
	{
		if (mVx <= 0)
		{
			mVx = -mVx;
		}
		SetX(GetX() + mVx);
		isMove = true;
	}
	//��Ɉړ�
	if (mInput.Key('W'))
	{
		//�X�e�[�^�X���ړ����ҋ@�������̍��W��250�����̎�
		if (mState != EState::EMOVE || mState != EState::EWAIT)
		{
			if (GetY() - PLAYER_BOTTOM < 250)
			{
				SetY(GetY() + VELOCITY_PLAYER);
				isMove = true;
			}
		}
		//�X�e�[�^�X���W�����v���W�����v�J�n���̍��W��250�ȉ��̎�
		if (mState == EState::EJUMP && mJump < 250)
		{
			//�W�����v�������Z
			mJump += VELOCITY_PLAYER;
			SetY(GetY() + VELOCITY_PLAYER);
		}
	}
	//���Ɉړ�
	if (mInput.Key('S'))
	{
		//�X�e�[�^�X���ړ����ҋ@�������̍��W��0���傫����
		if (mState == EState::EMOVE || mState == EState::EWAIT)
		{
			if (GetY() - PLAYER_BOTTOM > 0)
			{
				SetY(GetY() - VELOCITY_PLAYER);
				isMove = true;
			}
		}
		//�X�e�[�^�X���W�����v���W�����v�J�n���̍��W��0���傫����
		if (mState == EState::EJUMP && mJump > 0)
		{
			//�W�����v�������Z
			mJump -= VELOCITY_PLAYER;
			SetY(GetY() - VELOCITY_PLAYER);
		}
	}
	//�W�����v
	if (mInput.Key(VK_SPACE))
	{
		if (mState != EState::EJUMP)
		{
			//�W�����v�̊J�n����Y���W���擾
			mJump = (GetY() - PLAYER_BOTTOM);
			//�W�����v�̏����x��ݒ�
			mVy = JUMPV0;
			//��Ԃ��W�����v�ɕύX
			mState = EState::EJUMP;
		}
	}
}

//���S����
void CPlayer::Death()
{
	//�^�X�N���X�g����폜
	SetEnabled(false);
}


//�ړ��A�j���[�V����
void CPlayer::MoveAnimation()
{
	//�摜��؂�ւ��鑬�x
	const int PITCH = 64;
	//X���W��ۑ�
	int PosX = (int)GetX();


	//X���W��0�ȏ�̎�
	if ((int)GetX() >= 0)
	{
		if (PosX % PITCH < PITCH / 6)
		{
			//���ړ�
			if (mVx < 0.0f)
			{
				Texture(GetTexture(), TEX_LEFTMOVE6);
			}
			//�E�ړ�
			else
			{
				Texture(GetTexture(), TEX_RIGHTMOVE1);
			}
		}
		else if (PosX % PITCH < PITCH * 2 / 6)
		{
			//���ړ�
			if (mVx < 0.0f)
			{
				Texture(GetTexture(), TEX_LEFTMOVE5);
			}
			//�E�ړ�
			else
			{
				Texture(GetTexture(), TEX_RIGHTMOVE2);
			}
		}
		else if (PosX % PITCH < PITCH * 3 / 6)
		{
			//���ړ�
			if (mVx < 0.0f)
			{
				Texture(GetTexture(), TEX_LEFTMOVE4);
			}
			//�E�ړ�
			else
			{
				Texture(GetTexture(), TEX_RIGHTMOVE3);
			}
		}
		else if (PosX % PITCH < PITCH * 4 / 6)
		{
			//���ړ�
			if (mVx < 0.0f)
			{
				Texture(GetTexture(), TEX_LEFTMOVE3);
			}
			//�E�ړ�
			else
			{
				Texture(GetTexture(), TEX_RIGHTMOVE4);
			}
		}
		else if (PosX % PITCH < PITCH * 5 / 6)
		{
			//���ړ�
			if (mVx < 0.0f)
			{
				Texture(GetTexture(), TEX_LEFTMOVE2);
			}
			//�E�ړ�
			else
			{
				Texture(GetTexture(), TEX_RIGHTMOVE5);
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
				Texture(GetTexture(), TEX_RIGHTMOVE6);
			}
		}
	}
	//X���W��0�����̎�
	else
	{
		//�����ɂ���
		PosX = -PosX;

		if (PosX % PITCH < PITCH / 6)
		{
			//���ړ�
			if (mVx < 0.0f)
			{
				Texture(GetTexture(), TEX_LEFTMOVE1);
			}
			//�E�ړ�
			else
			{
				Texture(GetTexture(), TEX_RIGHTMOVE6);
			}
		}
		else if (PosX % PITCH < PITCH * 2 / 6)
		{
			//���ړ�
			if (mVx < 0.0f)
			{
				Texture(GetTexture(), TEX_LEFTMOVE2);
			}
			//�E�ړ�
			else
			{
				Texture(GetTexture(), TEX_RIGHTMOVE5);
			}
		}
		else if (PosX % PITCH < PITCH * 3 / 6)
		{
			//���ړ�
			if (mVx < 0.0f)
			{
				Texture(GetTexture(), TEX_LEFTMOVE3);
			}
			//�E�ړ�
			else
			{
				Texture(GetTexture(), TEX_RIGHTMOVE4);
			}
		}
		else if (PosX % PITCH < PITCH * 4 / 6)
		{
			//���ړ�
			if (mVx < 0.0f)
			{
				Texture(GetTexture(), TEX_LEFTMOVE4);
			}
			//�E�ړ�
			else
			{
				Texture(GetTexture(), TEX_RIGHTMOVE3);
			}
		}
		else if (PosX % PITCH < PITCH * 5 / 6)
		{
			//���ړ�
			if (mVx < 0.0f)
			{
				Texture(GetTexture(), TEX_LEFTMOVE5);
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
				Texture(GetTexture(), TEX_LEFTMOVE6);
			}
			//�E�ړ�
			else
			{
				Texture(GetTexture(), TEX_RIGHTMOVE1);
			}
		}
	}

}