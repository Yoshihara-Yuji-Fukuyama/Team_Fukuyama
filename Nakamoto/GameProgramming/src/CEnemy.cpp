#include "CEnemy.h"
#include "CPlayer.h"

//�m�F�p
#include <iostream>

//���A�E
//������
#define TEX_LEFT1 0,600
#define TEX_LEFT2 600,1200
#define TEX_LEFT3 1200,1800
#define TEX_LEFT4 1800,2400
#define TEX_LEFT5 2400,3000
#define TEX_LEFT6 3000,3600
//�E����
#define TEX_RIGHT1 600,0
#define TEX_RIGHT2 1200,600
#define TEX_RIGHT3 1800,1200
#define TEX_RIGHT4 2400,1800
#define TEX_RIGHT5 3000,2400
#define TEX_RIGHT6 3600,3000
//���A��
//�ړ�
#define TEX_MOVE 1200,600
//�ҋ@
#define TEX_WAIT 1800,1200


#define SLIME_BOTTOM 130                    //�X���C�������v�Z�p
#define ONI_BOTTOM 240                      //�S�����v�Z�p 
//�G�̈ړ����x
#define VELOCITY_ENEMY_X 2.0f                
#define VELOCITY_ENEMY_Y 1.0f

//static�ϐ��̒�`
CTexture CEnemy::mTextureSlime;
CTexture CEnemy::mTextureOni;

//���\�b�h�̒�`
CTexture* CEnemy::GetTextureSlime()
{
	return &mTextureSlime;
}

CTexture* CEnemy::GetTextureOni()
{
	return &mTextureOni;
}

//�G�̃f�t�H���g�R���X�g���N�^
CEnemy::CEnemy()
	:CCharacter((int)CTaskPriority::Object)
	, mCollider(this, &mX, &mY, &mZ, 140, 90, CCollider::EColliderType::ESLIME)
	, mFrame(0)
	, RandomX(rand() % 200)//200�܂łŃ����_��
	, RandomY(rand() % 100)//100�܂łŃ����_��
	, RandomTiming(rand() % 500)//500�܂łŃ����_��
{
}

//�G�̃R���X�g���N�^
CEnemy::CEnemy(float x, float y, float w, float h, int hp,
	EEnemyType enemyType)
	:CEnemy()
{
	Set(x, y, w, h);

	SetHp(hp);

	mState = EState::EWAIT;

	mVx = VELOCITY_ENEMY_X;

	mVy = VELOCITY_ENEMY_Y;

	SetZ(GetY() - SLIME_BOTTOM);

	mEnemyType = enemyType;

	

	if (mEnemyType == EEnemyType::Slime)
	{
		//�X���C���̉摜
		Texture(GetTextureSlime(), TEX_LEFT1, TEX_WAIT);
		//�����v�Z�p�ɃX���C��������
		mLeg = SLIME_BOTTOM;
		//�U���A�j���[�V������
		AttackNum = 4;
		//�ړ��A�j���[�V������
		MoveNum = 4;
		//�ҋ@�A�j���[�V������
		WaitNum = 4;

		mTag = ETag::ESLIME;
	}

	if (mEnemyType == EEnemyType::Oni)
	{
		//�S�̉摜
		Texture(GetTextureOni(), TEX_LEFT1, TEX_WAIT);
		//�����v�Z�p�ɋS������
		mLeg = ONI_BOTTOM;
		//�U���A�j���[�V������
		AttackNum = 6;
		//�ړ��A�j���[�V������
		MoveNum = 5;
		//�ҋ@�A�j���[�V������
		WaitNum = 4;

		mTag = ETag::ESLIME;
	}

}

//�f�X�g���N�^
CEnemy::~CEnemy()
{

}


void CEnemy::Update()
{
	//�������Ԃ�����
	SetSortOrder(GetY() - mLeg);
	switch (mState)
	{
	case EState::EWAIT://�ҋ@

		//�ړ��ł���悤�ɂȂ�ƃX�e�[�^�X���ړ��ɂȂ�
		Move();
		//�ҋ@�A�j���[�V����
		WaitAnimation(WaitNum);
		//�A�j���[�V������ݒ�
		SetAnimation();

		break;

	case EState::EMOVE://�ړ�
		//�ړ�����
		Move();

		//�ړ��A�j���[�V����
		MoveAnimation(GetX(), GetY(), isMoveX, isMoveY, mVx, MoveNum);
		//�A�j���[�V������ݒ�
		SetAnimation();

		break;
	}

}

void CEnemy::Move()
{
	const int MoveInterval = 500;
	int frame = mFrame++;
	int move;


	//frame/MoveInterval�̂��܂肪RandomTiming�̔{���Ȃ�
	if (frame % MoveInterval % RandomTiming == 0)
	{
		move = rand();//��������������_��
		//�����Ȃ�ړ�
		if (move % 2 == 0)
		{
			mState = EState::EMOVE;
		}
		//��Ȃ�ҋ@
		else
		{
			mState = EState::EWAIT;
		}
	}

	//�X�e�[�^�X���ړ��Ȃ�ړ�����
	if (mState == EState::EMOVE)
	{
		//�v���C���[�����ɂ���Ȃ獶�Ɉړ�
		if (CPlayer::GetInstance()->GetX() - GetX() < -RandomX)
		{
			//mVx�������Ȃ畉�̐��ɂ���
			if (mVx > 0)
			{
				mVx = -mVx;
				isMoveX = true;
				isMove = true;
			}
			//SetX(GetX() + mVx);
		}
		//�v���C���[���E�ɂ���Ȃ�E�Ɉړ�
		else if (CPlayer::GetInstance()->GetX() - GetX() > RandomX)
		{
			//mVx�����̐��Ȃ琳���ɂ���
			if (mVx < 0)
			{
				mVx = -mVx;
				isMoveX = true;
				isMove = true;
			}
			//SetX(GetX() + mVx);
		}
		else
		{
			isMoveX = false;
		}

		//�v���C���[�����ɂ���Ȃ牺�Ɉړ�
		if (CPlayer::GetInstance()->GetUnderPosY() - GetUnderPosY() < -RandomY)
		{
			//mVy�������Ȃ畉�̐��ɂ���
			if (mVy > 0)
			{
				mVy = -mVy;
				isMoveY = true;
				isMove = true;
			}
			//SetY(GetY() + mVy);
			SetZ(GetY() - SLIME_BOTTOM);
		}
		//�v���C���[����ɂ���Ȃ��Ɉړ�
		else if (CPlayer::GetInstance()->GetUnderPosY() - GetUnderPosY() > RandomY)
		{
			//mVy�����̐��Ȃ琳���ɂ���
			if (mVy < 0)
			{
				mVy = -mVy;
				isMoveY = true;
				isMove = true;
			}
			//SetY(GetY() + mVy);
			SetZ(GetY() - SLIME_BOTTOM);
		}
		else
		{
			isMoveY = false;
		}

		//�c�������ړ����Ă��Ȃ��Ȃ�ҋ@�Ɉڍs
		if (isMoveX == false && isMoveY == false)
		{
			isMove = false;
			mState = EState::EWAIT;
		}
	}
}

void CEnemy::Death()
{
	//�^�X�N���X�g����폜
	SetEnabled(false);
}

//�A�j���[�V������ݒ�
void CEnemy::SetAnimation()
{
	switch (mState)
	{
	case EState::EWAIT://�ҋ@�A�j���[�V����
		//������
		if (mVx < 0.0f)
		{
			if (mAnimationNum == CAnimationNumber::Move1)     Texture(GetTexture(), TEX_LEFT1, TEX_WAIT);
			else if (mAnimationNum == CAnimationNumber::Move2)Texture(GetTexture(), TEX_LEFT2, TEX_WAIT);
			else if (mAnimationNum == CAnimationNumber::Move3)Texture(GetTexture(), TEX_LEFT3, TEX_WAIT);
			else                                              Texture(GetTexture(), TEX_LEFT4, TEX_WAIT);
		}
		//�E����
		else
		{
			if (mAnimationNum == CAnimationNumber::Move1)     Texture(GetTexture(), TEX_RIGHT1, TEX_WAIT);
			else if (mAnimationNum == CAnimationNumber::Move2)Texture(GetTexture(), TEX_RIGHT2, TEX_WAIT);
			else if (mAnimationNum == CAnimationNumber::Move3)Texture(GetTexture(), TEX_RIGHT3, TEX_WAIT);
			else                                              Texture(GetTexture(), TEX_RIGHT4, TEX_WAIT);
		}

		break;
	case EState::EMOVE://�ړ��A�j���[�V����
		//���ړ�
		if (mVx < 0.0f)
		{
			if (mAnimationNum == CAnimationNumber::Move1)     Texture(GetTexture(), TEX_LEFT1, TEX_MOVE);
			else if (mAnimationNum == CAnimationNumber::Move2)Texture(GetTexture(), TEX_LEFT2, TEX_MOVE);
			else if (mAnimationNum == CAnimationNumber::Move3)Texture(GetTexture(), TEX_LEFT3, TEX_MOVE);
			else                                              Texture(GetTexture(), TEX_LEFT4, TEX_MOVE);
		}
		//�E�ړ�
		else
		{
			if (mAnimationNum == CAnimationNumber::Move1)     Texture(GetTexture(), TEX_RIGHT1, TEX_MOVE);
			else if (mAnimationNum == CAnimationNumber::Move2)Texture(GetTexture(), TEX_RIGHT2, TEX_MOVE);
			else if (mAnimationNum == CAnimationNumber::Move3)Texture(GetTexture(), TEX_RIGHT3, TEX_MOVE);
			else                                              Texture(GetTexture(), TEX_RIGHT4, TEX_MOVE);
		}

		break;
	}
}

CEnemy::EEnemyType CEnemy::GetEnemyType()
{
	return mEnemyType;
}

//�Փ˔���
void CEnemy::Collision(CCollider *m, CCollider *o)
{
	float ax, ay;

	switch (o->GetCType())
	{
	case CCollider::EColliderType::EPLAYER:

		//�R���C�_��m��o���Փ˂��Ă��邩���肵�Ă��邩����
		if (CCollider::Collision(m, o, &ax, &ay))
		{
			//�v���C���[�Ƃ̏Փ˔�������s(�߂荞�܂Ȃ�����)
			SetX(GetX() + ax);
			SetY(GetY() + ay);
		}
		break;
	case CCollider::EColliderType::EPATTACK1:
		//�R���C�_��m��o���Փ˂��Ă��邩���肵�Ă��邩����
		if (CCollider::Collision(m, o, &ax, &ay))
		{
			//�v���C���[�Ƃ̏Փ˔�������s(�߂荞�܂Ȃ�����)
			SetX(GetX() + 10);
			mHp -= 25;

		}

		std::cout << "HP�̒l��" << mHp << "�ł�\n";

		if (mHp <= 0)
		{
			mEnabled = false;
		}
		break;
	}
}

