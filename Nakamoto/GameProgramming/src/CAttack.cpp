#include "CAttack.h"
#include "CCollisionManager.h"

//�m�F�p �폜�\��
#include <stdio.h>

#define LIFE 50

#define ATTACK_X_POINT1 130	//�U��1�R���C�_�̐����ʒu��X���W�̉��Z�l
#define ATTACK_X_POINT2 120	//�U��2�R���C�_�̐����ʒu��X���W�̉��Z�l
#define ATTACK_X_POINT3 200	//�U��3�R���C�_�̐����ʒu��X���W�̉��Z�l

#define ATTACK_Y_POINT1 80	//1�i�ڂ̍U���R���C�_�̐����ʒu��Y���W�̉��Z�l
#define ATTACK_Y_POINT2 40  //2�i�ڂ̍U���R���C�_�̐����ʒu��Y���W�̉��Z�l

#define ATTACK_WIDTH1 130	//1�i�ڂ̕�
#define ATTACK_WIDTH2 120	//2�i�ڂ̕�
#define ATTACK_WIDTH3 70	//3�i�ڂ̕�

#define ATTACK_HEIGHT1 100	//1�i�ڂ̍���
#define ATTACK_HEIGHT2 170	//2�i�ڂ̍���
#define ATTACK_HEIGHT3 200	//3�i�ڂ̍���

#define ATTACK_X_POINT_S 110	//�X���C���̍U���̐����ʒu��X���W�̉��Z�l
#define ATTACK_Y_POINT_S 0	//�X���C���̍U���̐����ʒu��Y���W�̉��Z�l
#define ATTACK_WIDTH_S 60	//�X���C���̍U���̕�
#define ATTACK_HEIGHT_S 80	//�X���C���̍U���̍���

#define ATTACK_X_POINT_O 100	//�S�̍U���̐����ʒu��X���W�̉��Z�l
#define ATTACK_WIDTH_O 50		//�S�̍U���̕�
#define ATTACK_HEIGHT_O 200		//�S�̍U���̍���


CAttack::CAttack(CCharacter* parent, float* x, float* y, float* z, float mvx, int attackNumber)
	:CCharacter()
	,mLife(LIFE)
{
	mZ = *z;
	mVx = mvx;
	
	if (mVx < 0) 
	{
		//������
		//�v���C���[��1�i�ڂ̍U��
		if (attackNumber == 1)
		{
			mCollider.SetCollider(this, &mX, &mY, &mZ, ATTACK_WIDTH1, ATTACK_HEIGHT1, CCollider::EColliderType::EPATTACK1);
			mX = *x - ATTACK_X_POINT1;
			mY = *y + ATTACK_Y_POINT1;
			printf("���U��1\n");
		}
		//�v���C���[��2�i�ڂ̍U��
		else if (attackNumber == 2)
		{
			mCollider.SetCollider(this, &mX, &mY, &mZ, ATTACK_WIDTH2, ATTACK_HEIGHT2, CCollider::EColliderType::EPATTACK2);
			mX = *x - ATTACK_X_POINT2;
			mY = *y + ATTACK_Y_POINT2;
			printf("���U��2\n");
		}
		//�v���C���[��3�i�ڂ̍U��
		else if (attackNumber == 3)
		{
			mCollider.SetCollider(this, &mX, &mY, &mZ, ATTACK_WIDTH3, ATTACK_HEIGHT3, CCollider::EColliderType::EPATTACK3);
			mX = *x - ATTACK_X_POINT3;
			mY = *y;
			printf("���U��3\n");
		}
		//�X���C���̍U��
		else if (attackNumber == 4)
		{
			mCollider.SetCollider(this, &mX, &mY, &mZ, ATTACK_WIDTH_S, ATTACK_HEIGHT_S, CCollider::EColliderType::ESATTACK);
			mX = *x - ATTACK_X_POINT_S;
			mY = *y + ATTACK_Y_POINT_S;
		}
		//�S�̍U��
		else if (attackNumber == 5)
		{
			mCollider.SetCollider(this, &mX, &mY, &mZ, ATTACK_WIDTH_O, ATTACK_HEIGHT_O, CCollider::EColliderType::EOATTACK);
			mX = *x - ATTACK_X_POINT_O;
			mY = *y;
		}
	}
	else
	{
		//�E����
		//�v���C���[��1�i�ڂ̍U��
		if (attackNumber == 1)
		{
			mCollider.SetCollider(this, &mX, &mY, &mZ, ATTACK_WIDTH1, ATTACK_HEIGHT1, CCollider::EColliderType::EPATTACK1);
			mX = *x + ATTACK_X_POINT1;
			mY = *y + ATTACK_Y_POINT1;
			printf("�E�U��1\n");
		}
		//�v���C���[��2�i�ڂ̍U��
		else if (attackNumber == 2)
		{
			mCollider.SetCollider(this, &mX, &mY, &mZ, ATTACK_WIDTH2, ATTACK_HEIGHT2, CCollider::EColliderType::EPATTACK2);
			mX = *x + ATTACK_X_POINT2;
			mY = *y + ATTACK_Y_POINT2;
			printf("�E�U��2\n");
		}
		//�v���C���[��3�i�ڂ̍U��
		else if (attackNumber == 3)
		{
			mCollider.SetCollider(this, &mX, &mY, &mZ, ATTACK_WIDTH3, ATTACK_HEIGHT3, CCollider::EColliderType::EPATTACK3);
			mX = *x + ATTACK_X_POINT3;
			mY = *y;
			printf("�E�U��3\n");
		}
		//�X���C���̍U��
		else if (attackNumber == 4)
		{
			mCollider.SetCollider(this, &mX, &mY, &mZ, ATTACK_WIDTH_S, ATTACK_HEIGHT_S, CCollider::EColliderType::ESATTACK);
			mX = *x + ATTACK_X_POINT_S;
			mY = *y + ATTACK_Y_POINT_S;
		}
		//�S�̍U��
		else if (attackNumber == 5)
		{
			mCollider.SetCollider(this, &mX, &mY, &mZ, ATTACK_WIDTH_O, ATTACK_HEIGHT_O, CCollider::EColliderType::EOATTACK);
			mX = *x + ATTACK_X_POINT_O;
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

//�`��(�����ƃG���[�ɂȂ�)
void CAttack::Render()
{

}