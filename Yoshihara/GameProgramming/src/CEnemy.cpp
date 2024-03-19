#include "CEnemy.h"
#include "CPlayer.h"
#include "CUiFont.h"

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


#define SLIME_BOTTOM 138                    //�X���C�������v�Z�p
#define ONI_BOTTOM 240                      //�S�����v�Z�p 

#define SLIME_SHADOW_WAIT 20               //�X���C���̑ҋ@���̉e�v�Z�p
#define SLIME_SHADOW_MOVE 40               //�X���C���̈ړ����̉e�v�Z�p
#define SLIME_SHADOW_ATTACK 70             //�X���C���̍U�����̉e�v�Z�p

#define SLIME_SHADOW_SIZE_WAIT 200,180      //�X���C���̑ҋ@���̉e�̑傫��
#define SLIME_SHADOW_SIZE_MOVE 200,180      //�X���C���̈ړ����̉e�̑傫��
#define SLIME_SHADOW_SIZE_ATTACK 200,180    //�X���C���̍U�����̉e�̑傫��

#define ONI_SHADOW_WAIT 200               //�S�̑ҋ@���̉e�v�Z�p
#define ONI_SHADOW_MOVE 200               //�S�̈ړ����̉e�v�Z�p
#define ONI_SHADOW_ATTACK 200             //�S�̍U�����̉e�v�Z�p

#define ONI_SHADOW_SIZE_WAIT 200,100      //�S�̑ҋ@���̉e�̑傫��
#define ONI_SHADOW_SIZE_MOVE 200,100      //�S�̈ړ����̉e�̑傫��
#define ONI_SHADOW_SIZE_ATTACK 200,100    //�S�̍U�����̉e�̑傫��

//�G�̈ړ����x
#define VELOCITY_ENEMY_X 2.0f                
#define VELOCITY_ENEMY_Y 1.0f
//�G�̌��j�|�C���g
#define SLIME_POINT 1000
#define ONI_POINT 2000

//static�ϐ��̒�`
CTexture CEnemy::mTextureSlime;
CTexture CEnemy::mTextureOni;
int CEnemy::mEnemyCount = 0;

//���\�b�h�̒�`
CTexture* CEnemy::GetTextureSlime()
{
	return &mTextureSlime;
}

CTexture* CEnemy::GetTextureOni()
{
	return &mTextureOni;
}

int CEnemy::GetEnemyCount()
{
	return mEnemyCount;
}

void CEnemy::ZeroEnemyCount()
{
	mEnemyCount = 0;
}

void CEnemy::PlusEnemyCount()
{
	mEnemyCount++;
}

//�G�̃f�t�H���g�R���X�g���N�^
CEnemy::CEnemy()
	:CCharacter((int)CTaskPriority::Object)
	, mColider(this, &mX, &mY, &mZ, 140, 90)
	, mFrame(0)
	//�G���v���C���[�ɋ߂Â��鋗��
	, RandomX(rand() % 100 + 50)//50����100�����܂łŃ����_��
	, RandomY(rand() % 50 + 50)//50����100�����܂łŃ����_��
	//�s���̊Ԋu
	, RandomTiming(rand() % 100 + 150)//250����500�����܂łŃ����_��
{
}

//�G�̃R���X�g���N�^
CEnemy::CEnemy(float x, float y, float w, float h, int hp, EEnemyType enemyType)
	:CEnemy()
{
	Set(x, y, w, h);

	SetHp(hp);

	mState = EState::EWAIT;

	mVx = VELOCITY_ENEMY_X;

	mVy = VELOCITY_ENEMY_Y;

	mEnemyType = enemyType;
	//�X���C���Ȃ�
	if (mEnemyType == EEnemyType::Slime)
	{
		//�X���C���̉摜
		Texture(GetTextureSlime(), TEX_LEFT1, TEX_WAIT);
		//�����v�Z�p�ɃX���C��������
		mLeg = SLIME_BOTTOM;	
		
		SetZ(GetY() - SLIME_BOTTOM);
		//�U���A�j���[�V������
		AttackNum = 4;
		//�ړ��A�j���[�V������
		MoveNum = 4;
		//�ҋ@�A�j���[�V������
		WaitNum = 4;

		mpShadow = new CShadow(GetX(), GetShadowPosY(), SLIME_SHADOW_SIZE_WAIT);
	}
	//�S�Ȃ�
	if (mEnemyType == EEnemyType::Oni)
	{
		//�S�̉摜
		Texture(GetTextureOni(), TEX_LEFT1, TEX_WAIT);
		//�����v�Z�p�ɋS������
		mLeg = ONI_BOTTOM;

		SetZ(GetY() - ONI_BOTTOM);
		//�U���A�j���[�V������
		AttackNum = 6;
		//�ړ��A�j���[�V������
		MoveNum = 5;
		//�ҋ@�A�j���[�V������
		WaitNum = 4;

		mpShadow = new CShadow(GetX(), GetShadowPosY(), ONI_SHADOW_SIZE_WAIT);
	}

}

void CEnemy::Update()
{
	//���ꂽ�G�͏�������
	if (CPlayer::GetInstance()->GetX() - GetX() > 1920 || CPlayer::GetInstance()->GetX() - GetX() < -1920)
	{
		SetEnabled(false);
	}
	//�������Ԃ�����
	SetSortOrder(GetY() - mLeg);
	switch (mState)
	{
	case EState::EWAIT://�ҋ@
		
		if (mEnemyType == EEnemyType::Slime)
		{
			//�e�̍���
			mShadow = SLIME_SHADOW_WAIT;
			//�e�̑傫��
			mpShadow->SetShadow(GetX(), GetShadowPosY(), SLIME_SHADOW_SIZE_WAIT);
		}
		else
		{
			//�e�̍���
			mShadow = ONI_SHADOW_WAIT;
			//�e�̑傫��
			mpShadow->SetShadow(GetX(), GetShadowPosY(), ONI_SHADOW_SIZE_WAIT);
		}


		//�ړ��ł���悤�ɂȂ�ƃX�e�[�^�X���ړ��ɂȂ�
		Move();
		//�ҋ@�A�j���[�V����
		WaitAnimation(WaitNum);
		//�A�j���[�V������ݒ�
		SetAnimation();

		break;
		
	case EState::EMOVE://�ړ�

		if (mEnemyType == EEnemyType::Slime)
		{
			//�e�̍���
			mShadow = SLIME_SHADOW_MOVE;
			//�e�̑傫��
			mpShadow->SetShadow(GetX(), GetShadowPosY(), SLIME_SHADOW_SIZE_MOVE);
		}
		else
		{
			//�e�̍���
			mShadow = ONI_SHADOW_MOVE;
			//�e�̑傫��
			mpShadow->SetShadow(GetX(), GetShadowPosY(), ONI_SHADOW_SIZE_MOVE);
		}

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
	const int MoveInterval = 250;
	int frame = mFrame++;
	int move;


	//frame/MoveInterval�̂��܂肪RandomTiming�̔{���Ȃ�
	if (frame % MoveInterval % RandomTiming == 0)
	{
			mState = EState::EMOVE;
	}

	//�X�e�[�^�X���ړ��Ȃ�ړ�����
	if (mState == EState::EMOVE)
	{
		//�v���C���[���E�ɂ���Ȃ�E�Ɉړ�
		if (CPlayer::GetInstance()->GetX() - GetX() > RandomX)
		{
			//mVx�����̐��Ȃ琳���ɂ���
			if (mVx < 0)
			{
				mVx = -mVx;
			}
			SetX(GetX() + mVx);
			isMoveX = true;
			isMove = true;
		}
		//�v���C���[�����ɂ���Ȃ獶�Ɉړ�
		else if (CPlayer::GetInstance()->GetX() - GetX() < -RandomX)
		{
			//mVx�������Ȃ畉�̐��ɂ���
			if (mVx > 0)
			{
				mVx = -mVx;
			}
			SetX(GetX() + mVx);
			isMoveX = true;
			isMove = true;
		}
		else
		{
			isMoveX = false;
		}
		//�v���C���[����ɂ���Ȃ��Ɉړ�
		if (CPlayer::GetInstance()->GetUnderPosY() - GetUnderPosY() > RandomY)
		{
			//mVy�����̐��Ȃ琳���ɂ���
			if (mVy < 0)
			{
				mVy = -mVy;
			}
			SetY(GetY() + mVy);
			SetZ(GetY() - SLIME_BOTTOM);
			isMoveY = true;
			isMove = true;
		}
		//�v���C���[�����ɂ���Ȃ牺�Ɉړ�
		else if (CPlayer::GetInstance()->GetUnderPosY() - GetUnderPosY() < -RandomY)
		{
			//mVy�������Ȃ畉�̐��ɂ���
			if (mVy > 0)
			{
				mVy = -mVy;
			}
			SetY(GetY() + mVy);
			SetZ(GetY() - SLIME_BOTTOM);
			isMoveY = true;
			isMove = true;
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

//�f�X�g���N�^
CEnemy::~CEnemy()
{
	mEnemyCount--;
	if (mHp <= 0)
	{
		if (mEnemyType == EEnemyType::Oni)
		{
			CUiFont::GetInstance()->SetScore(ONI_POINT);
		}
		else
		{
			CUiFont::GetInstance()->SetScore(SLIME_POINT);
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
			else                                              Texture(GetTexture(), TEX_RIGHT4, TEX_MOVE);
		}
		//���ړ�
		else
		{
			if (mAnimationNum == CAnimationNumber::Move1)     Texture(GetTexture(), TEX_LEFT1, TEX_MOVE);
			else if (mAnimationNum == CAnimationNumber::Move2)Texture(GetTexture(), TEX_LEFT2, TEX_MOVE);
			else if (mAnimationNum == CAnimationNumber::Move3)Texture(GetTexture(), TEX_LEFT3, TEX_MOVE);
			else                                              Texture(GetTexture(), TEX_LEFT4, TEX_MOVE);
		}
		break;
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
	}
}

