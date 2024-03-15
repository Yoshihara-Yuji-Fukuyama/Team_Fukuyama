#include "CEnemy.h"
#include "CPlayer.h"

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
#define ONI_BOTTOM 240                      //�S�����v�Z�p
#define VELOCITY_ENEMY 2.0f                 //�G�̈ړ����x

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
	, mColider(this, &mX, &mY, &mZ, 140, 90)
	, mFrame(0)
	,mLif(3)
	, RandomX(rand() % 200)//200�܂łŃ����_��
	, RandomY(rand() % 100)//100�܂łŃ����_��
	, RandomTiming(rand() % 500)//500�܂łŃ����_��
{
}

//�G�̃R���X�g���N�^
CEnemy::CEnemy(float x, float y, float w, float h, EEnemyType enemyType)
	:CEnemy()
{
	Set(x, y, w, h);

	mState = EState::EWAIT;

	mVx = VELOCITY_ENEMY;

	mVy = VELOCITY_ENEMY;

	SetZ(GetY() - SLIME_BOTTOM);

	mEnemyType = enemyType;

	if (mEnemyType == EEnemyType::Slime)
	{
		//�X���C���̉摜
		Texture(GetTextureSlime(), TEX_LEFTWAIT1);
		//�����v�Z�p�ɃX���C��������
		mLeg = SLIME_BOTTOM;
		//�U���A�j���[�V������
		AttackNum = 4;
		//�ړ��A�j���[�V������
		MoveNum = 4;
		//�ҋ@�A�j���[�V������
		WaitNum = 4;
	}

	if (mEnemyType == EEnemyType::Oni)
	{
		//�S�̉摜
		Texture(GetTextureOni(), TEX_LEFTWAIT1);
		//�����v�Z�p�ɋS������
		mLeg = ONI_BOTTOM;
		//�U���A�j���[�V������
		AttackNum = 6;
		//�ړ��A�j���[�V������
		MoveNum = 5;
		//�ҋ@�A�j���[�V������
		WaitNum = 4;
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
			if (mAnimationNum == CAnimationNumber::Move1)     Texture(GetTexture(), TEX_LEFTWAIT1);
			else if (mAnimationNum == CAnimationNumber::Move2)Texture(GetTexture(), TEX_LEFTWAIT2);
			else if (mAnimationNum == CAnimationNumber::Move3)Texture(GetTexture(), TEX_LEFTWAIT3);
			else                                              Texture(GetTexture(), TEX_LEFTWAIT4);
		}
		//�E����
		else
		{
			if (mAnimationNum == CAnimationNumber::Move1)     Texture(GetTexture(), TEX_RIGHTWAIT1);
			else if (mAnimationNum == CAnimationNumber::Move2)Texture(GetTexture(), TEX_RIGHTWAIT2);
			else if (mAnimationNum == CAnimationNumber::Move3)Texture(GetTexture(), TEX_RIGHTWAIT3);
			else                                              Texture(GetTexture(), TEX_RIGHTWAIT4);
		}

		break;
	case EState::EMOVE://�ړ��A�j���[�V����
		//���ړ�
		if (mVx < 0.0f)
		{
			if (mAnimationNum == CAnimationNumber::Move1)     Texture(GetTexture(), TEX_LEFTMOVE1);
			else if (mAnimationNum == CAnimationNumber::Move2)Texture(GetTexture(), TEX_LEFTMOVE2);
			else if (mAnimationNum == CAnimationNumber::Move3)Texture(GetTexture(), TEX_LEFTMOVE3);
			else                                              Texture(GetTexture(), TEX_LEFTMOVE4);
		}
		//�E�ړ�
		else
		{
			if (mAnimationNum == CAnimationNumber::Move1)     Texture(GetTexture(), TEX_RIGHTMOVE1);
			else if (mAnimationNum == CAnimationNumber::Move2)Texture(GetTexture(), TEX_RIGHTMOVE2);
			else if (mAnimationNum == CAnimationNumber::Move3)Texture(GetTexture(), TEX_RIGHTMOVE3);
			else                                              Texture(GetTexture(), TEX_RIGHTMOVE4);
		}

		break;
	}
}

void CEnemy::Collision(CCollider* m, CCollider* o)
{
	float ax, ay;
	//�R���C�_��m��o���Փ˂��Ă��邩���肵�Ă��邩����

	if (CCollider::Collision(m, o, &ax, &ay ))
	{
		//�v���C���[�Ƃ̏Փ˔�������s(�߂荞�܂Ȃ�����)
		SetX(GetX() + ax);
		SetY(GetY() + ay);
		mLif--;
		
		if (mLif < 0)
		{
			mEnabled = false;
		}

	}
}

