#include "CAttack.h"
#include "CCollisionManager.h"

//�m�F�p �폜�\��
#include <stdio.h>


#define LIFE 50

#define ATTACK_X_POINT 200	//�U���R���C�_�̐����ʒu��X���W�̉��Z�l

#define ATTACK_Y_POINT1 80	//1�i�ڂ̍U���R���C�_�̐����ʒu��Y���W�̉��Z�l

//�G���[���o��
//#define ATTACK_Y_POINT2 20�@//2�i�ڂ̍U���R���C�_�̐����ʒu��Y���W�̉��Z�l

#define ATTACK_WIDTH 70	//�U���R���C�_�̕�

#define ATTACK_HEIGHT1 120	//1�i�ڂ̍���
#define ATTACK_HEIGHT2 150	//2�i�ڂ̍���
#define ATTACK_HEIGHT3 200	//3�i�ڂ̍���


CAttack::CAttack(CCharacter* parent, float* x, float* y, float* z, float mvx, int attackNumber)
	:CCharacter(*z)
	,mLife(LIFE)
{
	mZ = *z;
	mVx = mvx;
	
	if (mVx < 0) 
	{
		//������
		if (attackNumber == 1)
		{
			mCollider.SetCollider(this, &mX, &mY, &mZ, ATTACK_WIDTH, ATTACK_HEIGHT1, CCollider::EColliderType::EPATTACK1);
			mX = *x - ATTACK_X_POINT;
			mY = *y + ATTACK_Y_POINT1;
			printf("���U��1\n");
		}
		else if (attackNumber == 2)
		{
			mCollider.SetCollider(this, &mX, &mY, &mZ, ATTACK_WIDTH, ATTACK_HEIGHT2, CCollider::EColliderType::EPATTACK2);
			mX = *x - ATTACK_X_POINT;
			mY = *y + 20;
			printf("���U��2\n");
		}
		else if (attackNumber == 3)
		{
			mCollider.SetCollider(this, &mX, &mY, &mZ, ATTACK_WIDTH, ATTACK_HEIGHT3, CCollider::EColliderType::EPATTACK3);
			mX = *x - ATTACK_X_POINT;
			mY = *y;
			printf("���U��3\n");
		}
		else if (attackNumber == 4)
		{
			mCollider.SetCollider(this, &mX, &mY, &mZ, 150, 100, CCollider::EColliderType::ESATTACK);
			mX = *x;
			mY = *y;
		}
		else if (attackNumber == 5)
		{
			mCollider.SetCollider(this, &mX, &mY, &mZ, ATTACK_WIDTH, ATTACK_HEIGHT3, CCollider::EColliderType::EOATTACK);
			mX = *x - ATTACK_X_POINT;
			mY = *y;
		}
	}
	else
	{
		//�E����
		if (attackNumber == 1)
		{
			mCollider.SetCollider(this, &mX, &mY, &mZ, ATTACK_WIDTH, ATTACK_HEIGHT1, CCollider::EColliderType::EPATTACK1);
			mX = *x + ATTACK_X_POINT;
			mY = *y + ATTACK_Y_POINT1;
			printf("�E�U��1\n");
		}
		else if (attackNumber == 2)
		{
			mCollider.SetCollider(this, &mX, &mY, &mZ, ATTACK_WIDTH, ATTACK_HEIGHT2, CCollider::EColliderType::EPATTACK2);
			mX = *x + ATTACK_X_POINT;
			mY = *y + 20;
			printf("�E�U��2\n");
		}
		else if (attackNumber == 3)
		{
			mCollider.SetCollider(this, &mX, &mY, &mZ, ATTACK_WIDTH, ATTACK_HEIGHT3, CCollider::EColliderType::EPATTACK3);
			mX = *x + ATTACK_X_POINT;
			mY = *y;
			printf("�E�U��3\n");
		}
		else if (attackNumber == 4)
		{
			mCollider.SetCollider(this, &mX, &mY, &mZ, 200, 20, CCollider::EColliderType::ESATTACK);
			mX = *x + ATTACK_X_POINT;
			mY = *y;
		}
		else if (attackNumber == 5)
		{
			mCollider.SetCollider(this, &mX, &mY, &mZ, ATTACK_WIDTH, ATTACK_HEIGHT3, CCollider::EColliderType::EOATTACK);
			mX = *x + ATTACK_X_POINT;
			mY = *y;
		}
	}	
}

void CAttack::Update()
{
	//�R���C�_�̐�������
	if (--mLife < 0)
	{
		mEnabled = false;
	}
}

void CAttack::Collision(CCharacter* m, CCharacter* o)
{
	
}

//�`��(�����ƃG���[�ɂȂ�)
void CAttack::Render()
{

}