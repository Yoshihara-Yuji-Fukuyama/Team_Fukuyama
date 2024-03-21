#include "CCollider.h"
#include "CCollisionManager.h"
#include "CCharacter.h"
#include "CEnemy.h"
//�m�F�p �폜�\��
#include <iostream>

#define HANI 60

CCollider::CCollider()
	:mpParent(nullptr)
{
}

CCollider::~CCollider()
{
	//�R���W�������X�g����폜
	CCollisionManager::GetInstance()->Remove(this);
}

CCollider::CCollider(CCharacter* parent,
	float* px, float* py, float* z, float w, float h, EColliderType cType)
	:CCollider()
{
	//�R���W�����}�l�[�W���ɒǉ�
	CCollisionManager::GetInstance()->Add(this);

	printf("�v���C���[�̃R���C�_�[����\n");//�m�F�p �폜�\��

	//�e�̐ݒ�
	mpParent = parent;

	mpX = px;	//X���W
	mpY = py;	//Y���W
	mLeg = z;	//�����̍��W
	mCW = w;	//����
	mCH = h;	//��
	mColliderType = cType;	//�R���C�_�̎��

}

void CCollider::SetCollider(CCharacter* parent,
	float* px, float* py, float* z, float w, float h, EColliderType cType)
{
	//�R���W�����}�l�[�W���ɒǉ�
	CCollisionManager::GetInstance()->Add(this);

	//�e�̐ݒ�
	mpParent = parent;

	mpX = px;	//X���W
	mpY = py;	//Y���W
	mLeg = z;	//�����̍��W
	mCW = w;	//����
	mCH = h;	//��
	mColliderType = cType;	//�R���C�_�̎��

}

void CCollider::Render()
{
	glBegin(GL_QUADS);
	glVertex2f(*mpX - mCW, *mpY - mCH);
	glVertex2f(*mpX + mCW, *mpY - mCH);
	glVertex2f(*mpX + mCW, *mpY + mCH);
	glVertex2f(*mpX - mCW, *mpY + mCH);
	glEnd();

}

CCollider::EColliderType CCollider::GetCType()
{
	return mColliderType;
}


//�Փ˔���
bool CCollider::Collision(CCollider* m, CCollider* o, float* ax, float* ay)
{
	//X���W�̓����蔻��
	if (*m->mpX < *o->mpX)
		*ax = *o->mpX - *m->mpX - m->mCW - o->mCW;
	else
		*ax = *m->mpX - *o->mpX - m->mCW - o->mCW;
	//0�ȏ�͏Փ˂��Ȃ�
	if (*ax >= 0.0f)
		return false;
	//Y���W�̓����蔻��
	if (*m->mpY < *o->mpY)
		*ay = *o->mpY - *m->mpY - m->mCH - o->mCH;
	else
		*ay = *m->mpY - *o->mpY - m->mCH - o->mCH;
	//0�ȏ�͏Փ˂��Ȃ�
	if (*ay >= 0.0f)
		return false;
	//���s�ŏՓ˂��Ă��邩
	if (*o->mLeg < *m->mLeg - HANI)
		return false;
	if (*o->mLeg > *m->mLeg + HANI)
		return false;

	//Y���Z��������
	if (*ax < *ay)
	{
		//Y�C���AX��0
		*ax = 0.0f;
		*ay = *o->mLeg - *m->mLeg - HANI;
		//��̎�
		if (*m->mLeg > *o->mLeg)
			*ay = *o->mLeg - *m->mLeg + HANI;
	}
	else
	{
		//X�C���AY��0
		*ay = 0.0f;
		//�E�̎�
		if (*m->mpX > *o->mpX)
			*ax = -*ax;
	}
	return true;
}

float CCollider::GetmpY()
{
	return *mpY;
}