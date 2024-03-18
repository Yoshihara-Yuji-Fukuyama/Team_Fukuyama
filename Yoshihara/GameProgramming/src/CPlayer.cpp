#include "CPlayer.h"
#include "CApplication.h"

//���A�E
//������
#define TEX_LEFT1 600,0
#define TEX_LEFT2 1200,600
#define TEX_LEFT3 1800,1200
#define TEX_LEFT4 2400,1800
#define TEX_LEFT5 3000,2400
#define TEX_LEFT6 3600,3000
//�E����
#define TEX_RIGHT1 0,600
#define TEX_RIGHT2 600,1200
#define TEX_RIGHT3 1200,1800
#define TEX_RIGHT4 1800,2400
#define TEX_RIGHT5 2400,3000
#define TEX_RIGHT6 3000,3600

//���A��
//�ҋ@
#define TEX_WAIT 3000,2400
//�ړ�
#define TEX_MOVE 2400,1800
//�W�����v
#define TEX_JUMP 3600,3000
//�U��1
#define TEX_ATTACK1 600,0
//�U��2
#define TEX_ATTACK2 1200,600
//�U��3
#define TEX_ATTACK3 1800,1200

#define PLAYER_STARTSET 100.0f,300.0f,300.0f,300.0f//x,y,w,h �v���C���[�̏����ʒu

#define PLAYER_HP 100                       //�v���C���[��HP
#define VELOCITY_PLAYER 6.0f	            //�v���C���[�̈ړ����x
#define JUMPV0 (30 / 1.4f)		            //�W�����v�̏����x
#define GRAVITY (30 / 30)		            //�d�͉����x

#define PLAYER_BOTTOM 270                   //�v���C���[�����v�Z�p

#define PLAYER_SHADOW_WAIT 240               //�v���C���[�ҋ@���̉e�v�Z�pdwsdwwwwww
#define PLAYER_SHADOW_JUMP 240               //�v���C���[�W�����v���̉e�v�Z�p
#define PLAYER_SHADOW_MOVE 220               //�v���C���[�ړ����̉e�v�Z�p
#define PLAYER_SHADOW_ATTACK 240             //�v���C���[�U�����̉e�v�Z�p

#define PLAYER_SHADOW_SIZE_WAIT 250,100      //�ҋ@���̉e�̑傫��
#define PLAYER_SHADOW_SIZE_JUMP 250,100      //�W�����v���̉e�̑傫��
#define PLAYER_SHADOW_SIZE_MOVE 350,100      //�ړ����̉e�̑傫��
#define PLAYER_SHADOW_SIZE_ATTACK 350,100    //�U�����̉e�̑傫��

#define PLAYER_SHADOW_POSX 20                //�e��X���W���Z�p


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
		mpInstance = new CPlayer(PLAYER_STARTSET, PLAYER_HP);
	}
	return mpInstance;
}


CPlayer::CPlayer()
	:CCharacter((int)CTaskPriority::Object)
	, mCollider(this, &mX, &mY, &mZ, 100, 100)
	, isClick(false)
{
	mState = EState::EWAIT;
	WaitNum = 4;//�ҋ@�A�j���[�V������
	MoveNum = 6;//�ړ��A�j���[�V������
	JumpNum = 4;//�W�����v�A�j���[�V������
	AttackNum = 6;//�U��1�A�j���[�V������+1
	AttackNum2 = 6;//�U��2�A�j���[�V������+1
	AttackNum3 = 5;//�U��3�A�j���[�V������+1
}

CPlayer::CPlayer(float x, float y, float w, float h, int hp)
	: CPlayer()
{
	Set(x, y, w, h);

	SetHp(hp);

	Texture(GetTexture(), TEX_LEFT1, TEX_WAIT);

	mVx = VELOCITY_PLAYER;

	mLeg = PLAYER_BOTTOM;

	SetZ(GetY() - mLeg);

	mAttackPhase = EAttackPhase::Attack0;

	mpShadow = new CShadow(GetX() - PLAYER_SHADOW_POSX, GetShadowPosY(), PLAYER_SHADOW_SIZE_WAIT);
}

CPlayer::~CPlayer()
{

}

void CPlayer::Update()
{
	switch (mState)
	{
	case EState::EWAIT:
		//�e�̍����v�Z�p
		mShadow = PLAYER_SHADOW_WAIT;
		//�e�̑傫��
		mpShadow->SetShadow(GetX() - PLAYER_SHADOW_POSX, GetShadowPosY(), PLAYER_SHADOW_SIZE_WAIT);

		//�������Ԃ�����
		SetSortOrder(GetY() - mLeg);

		//�ړ�����
		Move();

		//�ҋ@�A�j���[�V����
		WaitAnimation(WaitNum);
		//�A�j���[�V������ݒ�
		SetAnimation();

		if (isMove == true && mState != EState::EATTACK)
		{
			mState = EState::EMOVE;
		}

		break;
	case EState::EMOVE:
		//�e�̍����v�Z�p
		mShadow = PLAYER_SHADOW_MOVE;
		//�e�̑傫��
		mpShadow->SetShadow(GetX() - PLAYER_SHADOW_POSX, GetShadowPosY(), PLAYER_SHADOW_SIZE_MOVE);

		//�������Ԃ�����
		SetSortOrder(GetY() - mLeg);

		//�ړ�����
		Move();
		//�U������
		Attack();

		//�ړ��A�j���[�V����
		MoveAnimation(GetX(), GetY(), isMoveX, isMoveY, mVx, MoveNum);
		//�A�j���[�V������ݒ�
		SetAnimation();

		if (isMove == false && mState != EState::EATTACK)
		{
			mState = EState::EWAIT;
		}

		break;
	case EState::EJUMP://�W�����v����

		//�e�̍����v�Z�p
		mShadow = PLAYER_SHADOW_JUMP;
		//�e�̑傫��
		mpShadow->SetShadow(GetX() - PLAYER_SHADOW_POSX, GetShadowPosY(), PLAYER_SHADOW_SIZE_JUMP);

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
			//�ړ����Ă���Ȃ��Ԃ��ړ��ɕύX
			if (isMove == true)
			{
				mState = EState::EMOVE;
			}
			//���Ă��Ȃ��Ȃ��Ԃ�ҋ@�ɕύX
			else
			{
				mState = EState::EWAIT;
			}
		}
		//�W�����v���ɉ�ʉ���艺�ɍs���Ȃ��悤�ɂ���
		if (GetY() - mLeg < 0)
		{
			//�ړ����Ă���Ȃ��Ԃ��ړ��ɕύX
			if (isMove == true)
			{
				mState = EState::EMOVE;
			}
			//���Ă��Ȃ��Ȃ��Ԃ�ҋ@�ɕύX
			else
			{
				mState = EState::EWAIT;
			}
		}
		break;

	case EState::EATTACK:	//�U������
		
		//�e�̍����v�Z�p
		mShadow = PLAYER_SHADOW_ATTACK;
		//�e�̑傫��
		mpShadow->SetShadow(GetX() - PLAYER_SHADOW_POSX, GetShadowPosY(), PLAYER_SHADOW_SIZE_ATTACK);

        //�������Ԃ�����
		SetSortOrder(GetY() - mLeg);

		Move();
		//Attack();

		if (mAttackPhase == EAttackPhase::Attack1)
		{
			//�U���A�j���[�V����
			AttackAnimation(AttackNum);
		}
		else if (mAttackPhase == EAttackPhase::Attack2)
		{
			//�U���A�j���[�V����
			AttackAnimation(AttackNum2);
		}
		else if (mAttackPhase == EAttackPhase::Attack3)
		{
			//�U���A�j���[�V����
			AttackAnimation(AttackNum3);
		}

		//�A�j���[�V������ݒ�
		SetAnimation();


		//�U�����I������Ƃ��l�N�X�g��true�Ȃ玟�̍U����
		if (isAttack == false && isAttackNext == true)
		{
			mFrame = 0;
			isAttack = true;
			mAttackPhase = mAttackPhaseNext;
			isAttackNext = false;
		}
		//����false�Ȃ�U���I��
		else if (isAttack == false && isAttackNext == false)
		{
			mFrame = 0;
			mAttackPhase = EAttackPhase::Attack0;
			mState = EState::EWAIT;
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
	//�E�Ɉړ�
	if (mInput.Key('D') && mState != EState::EATTACK)
	{
		if (mVx <= 0)
		{
			mVx = -mVx;
		}
		SetX(GetX() + mVx);
		isMove = true;
		isMoveX = true;
	}
	//���Ɉړ�
	else if (mInput.Key('A') && mState != EState::EATTACK)
	{
		if (mVx > 0)
		{
			mVx = -mVx;
		}
		SetX(GetX() + mVx);
		isMove = true;
		isMoveX = true;
	}
	//��Ɉړ�
	if (mInput.Key('W') && mState != EState::EATTACK)
	{
		//�X�e�[�^�X���ړ����ҋ@�������̍��W��250�����̎�
		if (mState != EState::EMOVE || mState != EState::EWAIT)
		{
			if (GetY() - mLeg < 250)
			{
				SetY(GetY() + VELOCITY_PLAYER);
				SetZ(GetY() - mLeg);
				isMove = true;
				isMoveY = true;
			}
		}
		//�X�e�[�^�X���W�����v���W�����v�J�n���̍��W��250�ȉ��̎�
		if (mState == EState::EJUMP && mJump < 250)
		{
			//�W�����v�������Z
			mJump += VELOCITY_PLAYER;
			mShadowPosY += VELOCITY_PLAYER;
			SetY(GetY() + VELOCITY_PLAYER);
		}
	}
	//���Ɉړ�
	else if (mInput.Key('S') && mState != EState::EATTACK)
	{
		//�X�e�[�^�X���ړ����ҋ@�������̍��W��0���傫����
		if (mState == EState::EMOVE || mState == EState::EWAIT)
		{
			if (GetY() - mLeg > 0)
			{
				SetY(GetY() - VELOCITY_PLAYER);
				SetZ(GetY() - mLeg);
				isMove = true;
				isMoveY = true;
			}
		}
		//�X�e�[�^�X���W�����v���W�����v�J�n���̍��W��0���傫����
		if (mState == EState::EJUMP && mJump > 0)
		{
			//�W�����v�������Z
			mJump -= VELOCITY_PLAYER;
			mShadowPosY -= VELOCITY_PLAYER;
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
			mShadowPosY = (GetY() - mShadow);
			//�W�����v�̏����x��ݒ�
			mVy = JUMPV0;
			//��Ԃ��W�����v�ɕύX
			mState = EState::EJUMP;
			SetHp(50);
		}
	}
	//�U��
	if (mInput.Key(VK_LBUTTON) && mState != EState::EJUMP)
	{
		if (isClick == false)
		{
			if (isAttack == false && mAttackPhase == EAttackPhase::Attack0)
			{
				//�U���i�K����
				mAttackPhase = EAttackPhase::Attack1;

				isAttack = true;
			}
			else if (isAttackNext == false && mAttackPhase != EAttackPhase::Attack3)
			{
				//�U���i�K����
				if (mAttackPhase == EAttackPhase::Attack1)
				{
					mAttackPhaseNext = EAttackPhase::Attack2;
				}
				else if (mAttackPhase == EAttackPhase::Attack2)
				{
					mAttackPhaseNext = EAttackPhase::Attack3;
				}
				isAttackNext = true;
			}
			//�U���Ɉڍs
			mState = EState::EATTACK;
		}
		isClick = true;
	}
	else
	{
		isClick = false;
	}
}

void CPlayer::Attack()
{
	CAttack* attack = new CAttack(this, &mX, &mY);
	//attack->Set(GetX(), GetY(), 30, 100);
	//CCollisionManager::GetInstance()->Add(attack);
}

//���S����
void CPlayer::Death()
{
	//�^�X�N���X�g����폜
	SetEnabled(false);
}

bool CPlayer::GetMoveX()
{
	return isMoveX;
}

float CPlayer::GetmVx()
{
	return mVx;
}

//�A�j���[�V������ݒ�
void CPlayer::SetAnimation()
{
	switch (mState)
	{
	case EState::EWAIT://�ҋ@�A�j���[�V����
		//�E����
		if (mVx > 0.0f)
		{
			if (mAnimationNum == CAnimationNumber::Move1)     Texture(GetTexture(), TEX_RIGHT1, TEX_WAIT);
			else if (mAnimationNum == CAnimationNumber::Move2)Texture(GetTexture(), TEX_RIGHT2, TEX_WAIT);
			else if (mAnimationNum == CAnimationNumber::Move3)Texture(GetTexture(), TEX_RIGHT3, TEX_WAIT);
			else                                              Texture(GetTexture(), TEX_RIGHT4, TEX_WAIT);
		}
		//������
		else
		{
			if (mAnimationNum == CAnimationNumber::Move1)     Texture(GetTexture(), TEX_LEFT1, TEX_WAIT);
			else if (mAnimationNum == CAnimationNumber::Move2)Texture(GetTexture(), TEX_LEFT2, TEX_WAIT);
			else if (mAnimationNum == CAnimationNumber::Move3)Texture(GetTexture(), TEX_LEFT3, TEX_WAIT);
			else                                              Texture(GetTexture(), TEX_LEFT4, TEX_WAIT);
		}
		break;
	case EState::EMOVE://�ړ��A�j���[�V����
		//�E�ړ�
		if (mVx > 0.0f)
		{
			if (mAnimationNum == CAnimationNumber::Move1)     Texture(GetTexture(), TEX_RIGHT1, TEX_MOVE);
			else if (mAnimationNum == CAnimationNumber::Move2)Texture(GetTexture(), TEX_RIGHT2, TEX_MOVE);
			else if (mAnimationNum == CAnimationNumber::Move3)Texture(GetTexture(), TEX_RIGHT3, TEX_MOVE);
			else if (mAnimationNum == CAnimationNumber::Move4)Texture(GetTexture(), TEX_RIGHT4, TEX_MOVE);
			else if (mAnimationNum == CAnimationNumber::Move5)Texture(GetTexture(), TEX_RIGHT5, TEX_MOVE);
			else                                              Texture(GetTexture(), TEX_RIGHT6, TEX_MOVE);
		}
		//���ړ�
		else
		{
			if (mAnimationNum == CAnimationNumber::Move1)     Texture(GetTexture(), TEX_LEFT1, TEX_MOVE);
			else if (mAnimationNum == CAnimationNumber::Move2)Texture(GetTexture(), TEX_LEFT2, TEX_MOVE);
			else if (mAnimationNum == CAnimationNumber::Move3)Texture(GetTexture(), TEX_LEFT3, TEX_MOVE);
			else if (mAnimationNum == CAnimationNumber::Move4)Texture(GetTexture(), TEX_LEFT4, TEX_MOVE);
			else if (mAnimationNum == CAnimationNumber::Move5)Texture(GetTexture(), TEX_LEFT5, TEX_MOVE);
			else                                              Texture(GetTexture(), TEX_LEFT6, TEX_MOVE);
		}

		break;
	case EState::EJUMP://�W�����v�A�j���[�V����
		//�E����
		if (mVx > 0.0f)
		{
			if (mAnimationNum == CAnimationNumber::Move1)     Texture(GetTexture(), TEX_RIGHT1, TEX_JUMP);
			else if (mAnimationNum == CAnimationNumber::Move2)Texture(GetTexture(), TEX_RIGHT2, TEX_JUMP);
			else if (mAnimationNum == CAnimationNumber::Move3)Texture(GetTexture(), TEX_RIGHT3, TEX_JUMP);
			else                                              Texture(GetTexture(), TEX_RIGHT4, TEX_JUMP);
		}
		//������
		else
		{
			if (mAnimationNum == CAnimationNumber::Move1)     Texture(GetTexture(), TEX_LEFT1, TEX_JUMP);
			else if (mAnimationNum == CAnimationNumber::Move2)Texture(GetTexture(), TEX_LEFT2, TEX_JUMP);
			else if (mAnimationNum == CAnimationNumber::Move3)Texture(GetTexture(), TEX_LEFT3, TEX_JUMP);
			else                                              Texture(GetTexture(), TEX_LEFT4, TEX_JUMP);
		}
		break;
	case EState::EATTACK:	//�U���A�j���[�V����
        //�E����
		if (mVx > 0.0f)
		{
			if (isAttack == true)
			{
				if (mAttackPhase == EAttackPhase::Attack1)
				{
					//�U���A�j���[�V����
					if (mAnimationNum == CAnimationNumber::Move1)     Texture(GetTexture(), TEX_RIGHT1, TEX_ATTACK1);
					else if (mAnimationNum == CAnimationNumber::Move2)Texture(GetTexture(), TEX_RIGHT2, TEX_ATTACK1);
					else if (mAnimationNum == CAnimationNumber::Move3)Texture(GetTexture(), TEX_RIGHT3, TEX_ATTACK1);
					else if (mAnimationNum == CAnimationNumber::Move4)Texture(GetTexture(), TEX_RIGHT4, TEX_ATTACK1);
					else if (mAnimationNum == CAnimationNumber::Move5)Texture(GetTexture(), TEX_RIGHT5, TEX_ATTACK1);
					else isAttack = false;
				}
				else if (mAttackPhase == EAttackPhase::Attack2)
				{
					//�U���A�j���[�V����
					if (mAnimationNum == CAnimationNumber::Move1)     Texture(GetTexture(), TEX_RIGHT1, TEX_ATTACK2);
					else if (mAnimationNum == CAnimationNumber::Move2)Texture(GetTexture(), TEX_RIGHT2, TEX_ATTACK2);
					else if (mAnimationNum == CAnimationNumber::Move3)Texture(GetTexture(), TEX_RIGHT3, TEX_ATTACK2);
					else if (mAnimationNum == CAnimationNumber::Move4)Texture(GetTexture(), TEX_RIGHT4, TEX_ATTACK2);
					else if (mAnimationNum == CAnimationNumber::Move5)Texture(GetTexture(), TEX_RIGHT5, TEX_ATTACK2);
					else isAttack = false;
				}
				else if (mAttackPhase == EAttackPhase::Attack3)
				{
					//�U���A�j���[�V����
					if (mAnimationNum == CAnimationNumber::Move1)     Texture(GetTexture(), TEX_RIGHT1, TEX_ATTACK3);
					else if (mAnimationNum == CAnimationNumber::Move2)Texture(GetTexture(), TEX_RIGHT2, TEX_ATTACK3);
					else if (mAnimationNum == CAnimationNumber::Move3)Texture(GetTexture(), TEX_RIGHT3, TEX_ATTACK3);
					else if (mAnimationNum == CAnimationNumber::Move4)Texture(GetTexture(), TEX_RIGHT4, TEX_ATTACK3);
					else isAttack = false;
				}
			}
		}
		//������
		else
		{
			if (isAttack == true)
			{
				if (mAttackPhase == EAttackPhase::Attack1)
				{
					//�U���A�j���[�V����
					if (mAnimationNum == CAnimationNumber::Move1)     Texture(GetTexture(), TEX_LEFT1, TEX_ATTACK1);
					else if (mAnimationNum == CAnimationNumber::Move2)Texture(GetTexture(), TEX_LEFT2, TEX_ATTACK1);
					else if (mAnimationNum == CAnimationNumber::Move3)Texture(GetTexture(), TEX_LEFT3, TEX_ATTACK1);
					else if (mAnimationNum == CAnimationNumber::Move4)Texture(GetTexture(), TEX_LEFT4, TEX_ATTACK1);
					else if (mAnimationNum == CAnimationNumber::Move5)Texture(GetTexture(), TEX_LEFT5, TEX_ATTACK1);
					else isAttack = false;
				}
				else if (mAttackPhase == EAttackPhase::Attack2)
				{
					//�U���A�j���[�V����
					if (mAnimationNum == CAnimationNumber::Move1)     Texture(GetTexture(), TEX_LEFT1, TEX_ATTACK2);
					else if (mAnimationNum == CAnimationNumber::Move2)Texture(GetTexture(), TEX_LEFT2, TEX_ATTACK2);
					else if (mAnimationNum == CAnimationNumber::Move3)Texture(GetTexture(), TEX_LEFT3, TEX_ATTACK2);
					else if (mAnimationNum == CAnimationNumber::Move4)Texture(GetTexture(), TEX_LEFT4, TEX_ATTACK2);
					else if (mAnimationNum == CAnimationNumber::Move5)Texture(GetTexture(), TEX_LEFT5, TEX_ATTACK2);
					else isAttack = false;
				}
				else if (mAttackPhase == EAttackPhase::Attack3)
				{
					//�U���A�j���[�V����
					if (mAnimationNum == CAnimationNumber::Move1)     Texture(GetTexture(), TEX_LEFT1, TEX_ATTACK3);
					else if (mAnimationNum == CAnimationNumber::Move2)Texture(GetTexture(), TEX_LEFT2, TEX_ATTACK3);
					else if (mAnimationNum == CAnimationNumber::Move3)Texture(GetTexture(), TEX_LEFT3, TEX_ATTACK3);
					else if (mAnimationNum == CAnimationNumber::Move4)Texture(GetTexture(), TEX_LEFT4, TEX_ATTACK3);
					else isAttack = false;
				}
			}
		}
	}
}



