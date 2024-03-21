#include "CPlayer.h"
#include "CApplication.h"

//�m�F�p �폜�\��
#include <iostream>

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
//�h��A����
#define TEX_MOTION 4200,3600

//�X���C������󂯂�_���[�W��
#define SLIME_TAKE_DAMAGE 10
//�S����󂯂�_���[�W��
#define ONI_TAKE_DAMAGE 20
//���G����
#define INVINCIBLE 100

#define PLAYER_STARTSET 100.0f,300.0f,300.0f,300.0f//x,y,w,h �v���C���[�̏����ʒu

#define PLAYER_HP 100                       //�v���C���[��HP
#define VELOCITY_PLAYER 6.0f	            //�v���C���[�̈ړ����x
#define JUMPV0 (30 / 1.4f)		            //�W�����v�̏����x
#define GRAVITY (30 / 30)		            //�d�͉����x

#define PLAYER_BOTTOM 272                   //�v���C���[�����v�Z�p

#define PLAYER_SHADOW_WAIT 240               //�v���C���[�ҋ@���̉e�v�Z�p
#define PLAYER_SHADOW_JUMP 240               //�v���C���[�W�����v���̉e�v�Z�p
#define PLAYER_SHADOW_MOVE 220               //�v���C���[�ړ����̉e�v�Z�p
#define PLAYER_SHADOW_ATTACK 240             //�v���C���[�U�����̉e�v�Z�p

#define PLAYER_SHADOW_SIZE_WAIT 250,100      //�ҋ@���̉e�̑傫��
#define PLAYER_SHADOW_SIZE_JUMP 250,100      //�W�����v���̉e�̑傫��
#define PLAYER_SHADOW_SIZE_MOVE 350,100      //�ړ����̉e�̑傫��
#define PLAYER_SHADOW_SIZE_ATTACK 350,100    //�U�����̉e�̑傫��

#define PLAYER_SHADOW_POSX 20                //�e��X���W���Z�p

//�����̑�����
#define JUMP_POWER_AMOUNT 0.1
#define DEFENSE_POWER_AMOUNT 3
#define ATTACK_POWER_AMOUNT 5
#define ATTACK_NUM_AMOUNT 1
#define SPEED_POWER_AMOUNT 1


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
//�C���X�^���X�̍폜
void CPlayer::DeleteInstance()
{
	if (mpInstance != nullptr)
	{
		delete mpInstance;
		mpInstance = nullptr;
	}
}


CPlayer::CPlayer()
	:CCharacter((int)CTaskPriority::Object)
	, mCollider(this, &mX, &mY, &mZ, 100, 200, CCollider::EColliderType::EPLAYER)
	, isClick(false)
	, mInvincible(0)
{
	isAttack = false;
	isAttackNext = false;
	isHit = false;
	isGuard = false;
	mState = EState::EWAIT;
	WaitNum = 4;//�ҋ@�A�j���[�V������
	MoveNum = 6;//�ړ��A�j���[�V������
	JumpNum = 4;//�W�����v�A�j���[�V������
	AttackNum = 6;//�U��1�A�j���[�V������+1
	AttackNum2 = 6;//�U��2�A�j���[�V������+1
	AttackNum3 = 5;//�U��3�A�j���[�V������+1
	HitNum = 2;//�G�̍U�����󂯂����̃A�j���[�V������+1
	GuardNum = 1;//�h��A�j���[�V������
	//�����n�̌���
	mJumpPower = 1;
	mDeffensePower = 0;
	mAttackPower = 0;
	mAttackNumPower = 0;
	mSpeedPower = 0;
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
	//�v���C���[�̉e
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
			mFrame = 0;
		}
		
		if (isHit == true && isMove == false)
		{
			mState = EState::EHIT;
			mFrame = 0;
		}

		//�h��
		if (isGuard == true)
		{
			mState = EState::GUARD;
			mFrame = 0;
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

		//�ړ��A�j���[�V����
		MoveAnimation(GetX(), GetY(), isMoveX, isMoveY, mVx, MoveNum);
		//�A�j���[�V������ݒ�
		SetAnimation();

		if (isMove == false && mState != EState::EATTACK)
		{
			mState = EState::EWAIT;
		}
		else if (isHit == true)
		{
			mState = EState::EHIT;
			mFrame = 0;
		}

		//�h��
		if (isGuard == true)
		{
			mState = EState::GUARD;
			mFrame = 0;
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
		//�ړ�����
		Move();

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

		//�U���R���C�_�̐��� 
		if (isAttack == true && isCollider == true && mAnimationNum == CAnimationNumber::Move3)
		{
			if (mAttackNumber == 1)
			{
				//�U��1�i�ڂ̃R���C�_�̐��� 
				Attack();

				isCollider = false;
			}

		}
		else if (isAttack == true && isCollider1 == true && mAnimationNum == CAnimationNumber::Move3)
		{
			if (mAttackNumber == 2)
			{
				//�U��2�i�ڂ̃R���C�_�̐��� 
				Attack();

				isCollider1 = false;
			}
		}
		else if (isAttack == true && isCollider2 == true && mAnimationNum == CAnimationNumber::Move3)
		{
			if (mAttackNumber == 3)
			{
				//�U��3�i�ڂ̃R���C�_�̐��� 
				Attack();

				isCollider2 = false;
			}
		}
		//�U�����I������Ƃ��l�N�X�g��true�Ȃ玟�̍U����
		else if (isAttack == false && isAttackNext == true)
		{
			if (mAttackNumPower == 0)
			{
				isCollider = true;
			}
			else if (mAttackNumPower >= 2 && mAttackPhase == EAttackPhase::Attack2)
			{
				mAttackNumber = 3;
			}
			else if (mAttackNumPower >= 1 && mAttackPhase == EAttackPhase::Attack1)
			{
				mAttackNumber = 2;
			}
			else if (mAttackNumPower >= 1 && mAttackPhase == EAttackPhase::Attack2)
			{
				mAttackNumber = 1;
			}


			//�U���R���C�_�̐��� 
			//Attack();

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

		if (isHit == true)
		{
			mState = EState::EHIT;
			mAttackPhase = EAttackPhase::Attack0;
			isAttack = false;
			isAttackNext = false;
			mFrame = 0;
		}

		break;

	case EState::EHIT:
		//�e�̍����v�Z�p
		mShadow = PLAYER_SHADOW_WAIT;
		//�e�̑傫��
		mpShadow->SetShadow(GetX() - PLAYER_SHADOW_POSX, GetShadowPosY(), PLAYER_SHADOW_SIZE_WAIT);

		//�������Ԃ�����
		SetSortOrder(GetY() - mLeg);

		HitAnimation(HitNum);

		//�A�j���[�V������ݒ�
		SetAnimation();

		if (isHit == false)
		{
			mState = EState::EWAIT;
		}

		break;
	case EState::GUARD:
		//�e�̍����v�Z�p
		mShadow = PLAYER_SHADOW_WAIT;
		//�e�̑傫��
		mpShadow->SetShadow(GetX() - PLAYER_SHADOW_POSX, GetShadowPosY(), PLAYER_SHADOW_SIZE_WAIT);

		//�������Ԃ�����
		SetSortOrder(GetY() - mLeg);

		//�ړ�����
		Move();

		GuardAnimation(GuardNum);

		//�A�j���[�V������ݒ�
		SetAnimation();

		if (isGuard == false)
		{
			mState = EState::EWAIT;
		}

		break;
	}

	//���G����
	if (mInvincible > 0)
	{
		//���G���Ԓ����Z
		mInvincible--;
	}
}

//�ړ�����
void CPlayer::Move()
{
	isMove = false;
	isMoveX = false;
	isMoveY = false;
	//�E�Ɉړ�
	if (mInput.Key('D') && mState != EState::EATTACK && isHit == false && mState != EState::GUARD)
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
	else if (mInput.Key('A') && mState != EState::EATTACK && isHit == false && mState != EState::GUARD)
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
	if (mInput.Key('W') && mState != EState::EATTACK && isHit == false && mState != EState::GUARD)
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
	else if (mInput.Key('S') && mState != EState::EATTACK && isHit == false && mState != EState::GUARD)
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
	if (mInput.Key(VK_SPACE) && mState != EState::EATTACK && isHit == false && mState != EState::GUARD)
	{
		if (mState != EState::EJUMP)
		{
			//�W�����v�̊J�n����Y���W���擾
			mJump = (GetY() - mLeg);
			mShadowPosY = (GetY() - mShadow);
			//�W�����v�̏����x��ݒ�
			mVy = JUMPV0 * mJumpPower;
			//��Ԃ��W�����v�ɕύX
			mState = EState::EJUMP;
		}
	}
	//�U��
	if (mInput.Key(VK_LBUTTON) && mState != EState::EJUMP && isHit == false && mState != EState::GUARD)
	{
		if (isClick == false)
		{
			if (isAttack == false && mAttackPhase == EAttackPhase::Attack0)
			{
				mAttackNumber = 1;
				//�U���i�K����
				mAttackPhase = EAttackPhase::Attack1;

				isCollider = true;

				isAttack = true;
			}
			else if (isAttackNext == false && mAttackPhase != EAttackPhase::Attack3)
			{
				//�U���i�K����
				if (mAttackPhase == EAttackPhase::Attack1)
				{
					//�U���i�K������1�ȏ�Ȃ�U���i�K2�ֈڍs
					if (mAttackNumPower >= 1)
					{
						mAttackPhaseNext = EAttackPhase::Attack2;
						isCollider1 = true;
					}
					else
					{
						mAttackPhaseNext = EAttackPhase::Attack1;
						isCollider = true;
					}
				}
				else if (mAttackPhase == EAttackPhase::Attack2)
				{
					//�U���i�K������2�ȏ�Ȃ�U���i�K3�ֈڍs
					if (mAttackNumPower >= 2)
					{
						mAttackPhaseNext = EAttackPhase::Attack3;
						isCollider2 = true;
					}
					else
					{
						mAttackPhaseNext = EAttackPhase::Attack1;
						isCollider = true;
					}
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

	//�h��
	if (mInput.Key(VK_RBUTTON) && mState != EState::EATTACK)
	{
		if (isClick == false)
		{
			isGuard = true;
			mFrame = 0;
		}
	}
	else
	{
		isGuard = false;
	}
}

void CPlayer::Attack()
{
	CAttack* attack = new CAttack(this, &mX, &mY, &mZ, mVx, mAttackNumber);
	attack->Update();
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

void CPlayer::SetmVx()
{
	//�E�����Ȃ�
	if (mVx > 0)
	{
		mVx = VELOCITY_PLAYER + mSpeedPower;
	}
	//�������Ȃ�
	else
	{
		mVx = -(VELOCITY_PLAYER + mSpeedPower);
	}

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
	case EState::EHIT:	//�U�����󂯂����̃A�j���[�V����
		if (isHit == true)
		{
			//������
			if (mVx < 0.0f)
			{
				if (mAnimationNum == CAnimationNumber::Move1)Texture(GetTexture(), TEX_LEFT2, TEX_MOTION);
				else isHit = false;
			}
			else
			{
				if (mAnimationNum == CAnimationNumber::Move1)Texture(GetTexture(), TEX_RIGHT2, TEX_MOTION);
				else isHit = false;
			}
		}
		break;
	case EState::GUARD:	//�h��A�j���[�V����
		if (isGuard == true)
		{
			//������
			if (mVx < 0.0f)
			{
				if (mAnimationNum == CAnimationNumber::Move1)Texture(GetTexture(), TEX_LEFT1, TEX_MOTION);
				else isGuard = false;
			}
			else
			{
				if (mAnimationNum == CAnimationNumber::Move1)Texture(GetTexture(), TEX_RIGHT1, TEX_MOTION);
				else isGuard = false;
			}
		}
	}
}


void CPlayer::Collision(CCollider* m, CCollider* o)
{
	float ax, ay;

	switch (o->GetCType())
	{
	case CCollider::EColliderType::ESLIME:	//�X���C���̑̂̃R���C�_�Ƃ̏Փ˔���

		//�R���C�_��m��o���Փ˂��Ă��邩���肵�Ă��邩����
		if (CCollider::Collision(m, o, &ax, &ay))
		{
			//�v���C���[�Ƃ̏Փ˔�������s(�߂荞�܂Ȃ�����)
			//SetX(GetX() + ax);
			//������
			//SetY(GetY() + ay);


		}
		break;
	case CCollider::EColliderType::ESATTACK:	//�X���C���̍U���R���C�_�Ƃ̏Փ˔���
		//�R���C�_��m��o���Փ˂��Ă��邩���肵�Ă��邩����
		if (CCollider::Collision(m, o, &ax, &ay))
		{
			if (mState != EState::GUARD)
			{
				if (mInvincible == 0)
				{
					//�v���C���[�Ƃ̏Փ˔�������s(�߂荞�܂Ȃ�����)
					//SetX(GetX() + 20);
					//������
					//SetY(GetY() + ay);

					mHp -= SLIME_TAKE_DAMAGE - mDeffensePower;
					mInvincible = INVINCIBLE;
					isHit = true;
				}
			}
			else if (mState == EState::GUARD)
			{
				mAttackPhase = EAttackPhase::Attack1;
			}

		}
		break;
	case CCollider::EColliderType::EONI:	//�S�̑̂̃R���C�_�Ƃ̏Փ˔���
		//�R���C�_��m��o���Փ˂��Ă��邩���肵�Ă��邩����
		if (CCollider::Collision(m, o, &ax, &ay))
		{
			//�v���C���[�Ƃ̏Փ˔�������s(�߂荞�܂Ȃ�����)
			//SetX(GetX() + ax);
			//������
			//SetY(GetY() + ay);
		}
		break;
	case CCollider::EColliderType::EOATTACK:	//�S�̍U���R���C�_�Ƃ̏Փ˔���
		//�R���C�_��m��o���Փ˂��Ă��邩���肵�Ă��邩����
		if (CCollider::Collision(m, o, &ax, &ay))
		{
			if (mState != EState::GUARD)
			{
				if (mInvincible == 0)
				{
					//�v���C���[�Ƃ̏Փ˔�������s(�߂荞�܂Ȃ�����)
					//SetX(GetX() + 20);
					//������
					//SetY(GetY() + ay);

					mHp -= ONI_TAKE_DAMAGE - mDeffensePower;
					mInvincible = INVINCIBLE;
					isHit = true;
				}
			}
			else if (mState == EState::GUARD)
			{
				mAttackPhase = EAttackPhase::Attack1;
			}

		}
		break;
	}
}

void CPlayer::HealHp(float heal)
{
	mHp += PLAYER_HP * heal;
	if (mHp > PLAYER_HP)
	{
		mHp = PLAYER_HP;
	}
}

float CPlayer::GetJumpPower()
{
	return mJumpPower;
}

int CPlayer::GetAttackPower()
{
	return mAttackPower;
}

//�����ʂ̐ݒ�
void  CPlayer::SetJumpPower()
{
	mJumpPower += JUMP_POWER_AMOUNT;
}
void  CPlayer::SetDeffensePower()
{
	mDeffensePower += DEFENSE_POWER_AMOUNT;
}
void  CPlayer::SetAttackPower()
{
	mAttackPower += ATTACK_POWER_AMOUNT;
}
void  CPlayer::SetAttackNumPower()
{
	mAttackNumPower += ATTACK_NUM_AMOUNT;
}
void  CPlayer::SetSpeedPower()
{
	mSpeedPower += SPEED_POWER_AMOUNT;
}