#include "CPlayer.h"
#include "CApplication.h"

//�萔�̒�`
//���A�E�A���A��@�G�e�N�X�`���}�b�s���O
//�ҋ@
#define TEX_LEFTWAIT1 600,0,3000,2400
#define TEX_LEFTWAIT2 1200,600,3000,2400
#define TEX_LEFTWAIT3 1800,1200,3000,2400
#define TEX_LEFTWAIT4 2400,1800,3000,2400
#define TEX_RIGHTWAIT1 0,600,3000,2400
#define TEX_RIGHTWAIT2 600,1200,3000,2400
#define TEX_RIGHTWAIT3 1200,1800,3000,2400
#define TEX_RIGHTWAIT4 1800,2400,3000,2400
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
//�W�����v
#define TEX_LEFTJUMP1 600,0,3600,3000
#define TEX_LEFTJUMP2 1200,600,3600,3000
#define TEX_LEFTJUMP3 1800,1200,3600,3000
#define TEX_LEFTJUMP4 2400,1800,3600,3000
#define TEX_RIGHTJUMP1 0,600,3600,3000
#define TEX_RIGHTJUMP2 600,1200,3600,3000
#define TEX_RIGHTJUMP3 1200,1800,3600,3000
#define TEX_RIGHTJUMP4 1800,2400,3600,3000






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
	, mCollider(this, &mX, &mY, 100, 100)
{
	mState = EState::EWAIT;
	WaitNum = 4;//�ҋ@�A�j���[�V������
	MoveNum = 6;//�ړ��A�j���[�V������
	JumpNum = 4;//�W�����v�A�j���[�V������
}

CPlayer::CPlayer(float x, float y, float w, float h)
	: CPlayer()
{
	Set(x, y, w, h);

	Texture(GetTexture(), TEX_LEFTMOVE1);

	mVx = VELOCITY_PLAYER;

	mLeg = PLAYER_BOTTOM;
}

CPlayer::~CPlayer()
{

}

void CPlayer::Update()
{
	switch (mState)
	{
	case EState::EWAIT:

		//�������Ԃ�����
		SetSortOrder(GetY() - mLeg);

		//�ړ�����
		Move();
		//�ҋ@�A�j���[�V����
		WaitAnimation(WaitNum);
		//�A�j���[�V������ݒ�
		SetAnimation();

		if (isMove == true)
		{
			mState = EState::EMOVE;
		}

		break;
	case EState::EMOVE:

		//�������Ԃ�����
		SetSortOrder(GetY() - mLeg);

		//�ړ�����
		Move();
		//�ړ��A�j���[�V����
		MoveAnimation(GetX(), GetY(), isMoveX, isMoveY, mVx, MoveNum);
		//�A�j���[�V������ݒ�
		SetAnimation();

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
		//�W�����v�A�j���[�V����
		JumpAnimation(GetY(), mJump, JumpNum);
		//�A�j���[�V������ݒ�
		SetAnimation();

		//Y���W��Y�����x��������
		SetY(GetY() + mVy);
		//Y�����x�ɏd�͂����Z����
		mVy -= GRAVITY;

		//�W�����v�����ȉ���Y���W���Ȃ�����
		if (GetY() - mLeg < mJump)
		{
			//��Ԃ��ړ��ɕύX
			mState = EState::EMOVE;
		}
		//�W�����v���ɉ�ʉ���艺�ɍs���Ȃ��悤�ɂ���
		if (GetY() - mLeg < 0)
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
	isMoveX = false;
	isMoveY = false;
	//���Ɉړ�
	if (mInput.Key('A'))
	{
		if (mVx > 0)
		{
			mVx = -mVx;
		}
		SetX(GetX() + mVx);
		isMove = true;
		isMoveX = true;
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
		isMoveX = true;
	}
	//��Ɉړ�
	if (mInput.Key('W'))
	{
		//�X�e�[�^�X���ړ����ҋ@�������̍��W��250�����̎�
		if (mState != EState::EMOVE || mState != EState::EWAIT)
		{
			if (GetY() - mLeg < 250)
			{
				SetY(GetY() + VELOCITY_PLAYER);
				isMove = true;
				isMoveY = true;
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
			if (GetY() - mLeg > 0)
			{
				SetY(GetY() - VELOCITY_PLAYER);
				isMove = true;
				isMoveY = true;
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
			mJump = (GetY() - mLeg);
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

//�A�j���[�V������ݒ�
void CPlayer::SetAnimation()
{
	switch (mState)
	{
	case EState::EWAIT://�ҋ@�A�j���[�V����
		//������
		if (mVx < 0.0f)
		{
			if (mAnimationNum == CAnimationNumber::Move1)     Texture(GetTexture(), TEX_LEFTWAIT1);
			else if (mAnimationNum == CAnimationNumber::Move2)Texture(GetTexture(), TEX_LEFTWAIT2);
			else if (mAnimationNum == CAnimationNumber::Move3)Texture(GetTexture(), TEX_LEFTWAIT3);
			else                     Texture(GetTexture(), TEX_LEFTWAIT4);
		}
		//�E����
		else
		{
			if (mAnimationNum == CAnimationNumber::Move1)     Texture(GetTexture(), TEX_RIGHTWAIT1);
			else if (mAnimationNum == CAnimationNumber::Move2)Texture(GetTexture(), TEX_RIGHTWAIT2);
			else if (mAnimationNum == CAnimationNumber::Move3)Texture(GetTexture(), TEX_RIGHTWAIT3);
			else                     Texture(GetTexture(), TEX_RIGHTWAIT4);
		}
		break;
	case EState::EMOVE://�ړ��A�j���[�V����
		//���ړ�
		if (mVx < 0.0f)
		{
			if (mAnimationNum == CAnimationNumber::Move1)     Texture(GetTexture(), TEX_LEFTMOVE1);
			else if (mAnimationNum == CAnimationNumber::Move2)Texture(GetTexture(), TEX_LEFTMOVE2);
			else if (mAnimationNum == CAnimationNumber::Move3)Texture(GetTexture(), TEX_LEFTMOVE3);
			else if (mAnimationNum == CAnimationNumber::Move4)Texture(GetTexture(), TEX_LEFTMOVE4);
			else if (mAnimationNum == CAnimationNumber::Move5)Texture(GetTexture(), TEX_LEFTMOVE5);
			else                                              Texture(GetTexture(), TEX_LEFTMOVE6);
		}
		//�E�ړ�
		else
		{
			if (mAnimationNum == CAnimationNumber::Move1)     Texture(GetTexture(), TEX_RIGHTMOVE1);
			else if (mAnimationNum == CAnimationNumber::Move2)Texture(GetTexture(), TEX_RIGHTMOVE2);
			else if (mAnimationNum == CAnimationNumber::Move3)Texture(GetTexture(), TEX_RIGHTMOVE3);
			else if (mAnimationNum == CAnimationNumber::Move4)Texture(GetTexture(), TEX_RIGHTMOVE4);
			else if (mAnimationNum == CAnimationNumber::Move5)Texture(GetTexture(), TEX_RIGHTMOVE5);
			else                     Texture(GetTexture(), TEX_RIGHTMOVE6);
		}

		break;
	case EState::EJUMP://�W�����v�A�j���[�V����
		//������
		if (mVx < 0.0f)
		{
			if (mAnimationNum == CAnimationNumber::Move1)     Texture(GetTexture(), TEX_LEFTJUMP1);
			else if (mAnimationNum == CAnimationNumber::Move2)Texture(GetTexture(), TEX_LEFTJUMP2);
			else if (mAnimationNum == CAnimationNumber::Move3)Texture(GetTexture(), TEX_LEFTJUMP3);
			else                                              Texture(GetTexture(), TEX_LEFTJUMP4);
		}
		//�E����
		else
		{
			if (mAnimationNum == CAnimationNumber::Move1)     Texture(GetTexture(), TEX_RIGHTJUMP1);
			else if (mAnimationNum == CAnimationNumber::Move2)Texture(GetTexture(), TEX_RIGHTJUMP2);
			else if (mAnimationNum == CAnimationNumber::Move3)Texture(GetTexture(), TEX_RIGHTJUMP3);
			else                                              Texture(GetTexture(), TEX_RIGHTJUMP4);
		}
		break;
	}
}
