#include "CCollider.h"
#include "CCollisionManager.h"
#include <stdio.h>

CCollider::CCollider()
{
}

CCollider::~CCollider()
{
	//�R���W�������X�g����폜
	CCollisionManager::GetInstance()->Remove(this);
}

CCollider::CCollider(CCharacter* parent,
	float* px, float* py,float* z, float w, float h ,bool attack)
	:CCollider()
{
	//�R���W�����}�l�[�W���ɒǉ�
	CCollisionManager::GetInstance()->Add(this);
	printf("�R���C�_�[����");

	//�e�̐ݒ�
	mpParent = parent;
	
	mpX = px;	//X���W
	if (attack)
	{
		mX = 100;
	}

	mpY = py;	//Y���W
	mpZ = z;
	mCW = w;	//����
	mCH = h;	//��
}

CCharacter* CCollider::GetParent()
{
	return mpParent;
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

void CCollider::AttackCollider(CCharacter* parent, float x, float y, float w, float h)
{	
	//�R���W�����}�l�[�W���ɒǉ�
	CCollisionManager::GetInstance()->Add(this,true);
}

#define HANI 150

//�Փ˔���
bool CCollider::Collision(CCollider* m, CCollider* o, float *ax, float *ay)
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

	if (*o->mpZ > *m->mpY-HANI)
		return false;
	if (*o->mpZ < *m->mpY - 300)
		return false;

	//Y���Z��������
	if (*ax < *ay)
	{
		//Y�C���AX��0
		*ax = 0.0f;
		//��̎�
		if (*m->mpY > *o->mpY)
			*ay = -*ay;
	}
	else
	{
		//X�C���AY��0
		*ay = 0.0f;
		//��̎�
		if (*m->mpX > *o->mpX)
			*ax = -*ax;
	}
	return true;
}