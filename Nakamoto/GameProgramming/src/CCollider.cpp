#include "CCollider.h"
#include "CCollisionManager.h"

//�f�t�H���g�R���X�g���N�^
CCollider::CCollider()
{
	
}
//~�f�X�g���N�^
CCollider::~CCollider()
{
	//�R���W�������X�g����폜
	CCollisionManager::Instance()->Remove(this);
}

//�R���X�g���N�^
CCollider::CCollider(CCharacter* parent,
	float &x, float &y, float w, float h)
{
	//�Փ˃R���C�_�[�ɒǉ�
	CCollisionManager::Instance()->Add(this);

	//�e�̐ݒ�
	mpParent = parent;

	mpXC = &x;
	mpYC = &y;
	mWC = w;
	mHC = h;

}

//�e�N���X�̎擾
CCharacter* CCollider::GetParent()
{
	return mpParent;
}

//�Փˏ���
bool CCollider::Collision(CCollider* m, CCollider* o, float* ax, float* ay)
{
	if (m->mpXC < o->mpXC)
		*ax = o->mpXC - m->mpXC - m->mWC - o->mWC;
	else
		*ax = m->mpXC - o->mpXC - m->mWC - o->mWC;
	//0�ȏ�͏Փ˂��Ȃ�
	if (*ax >= 0.0f)
		return false;

	if (m->mpYC < o->mpYC)
		*ay = o->mpYC - m->mpYC - m->mHC - o->mHC;
	else
		*ay = m->mpYC - o->mpYC - m->mHC - o->mHC;
	//0�ȏ�͏Փ˂��Ȃ�
	if (*ay >= 0.0f)
		return false;

	//Y���Z��������
	if (*ax < *ay)
	{
		//Y�C���AX��0
		*ax = 0.0f;
		//��̎�
		if (m->mpYC > o->mpYC)
			*ay = -*ay;
	}
	else
	{
		//X�C���AY��0
		*ay = 0.0f;
		//�E�̎�
		if (m->mpXC > o->mpXC)
			*ax = -*ax;
	}
	return true;
}

void CCollider::ChanegePriority(int priority)
{
	mPriority = priority;
	CCollisionManager::Instance()->Remove(this);	//��U�폜
	CCollisionManager::Instance()->Add(this);
}

//�`��
void CCollider::Render()
{
	//�l�p�`�ŕ`��
	glBegin(GL_QUADS);
	glVertex2f(*mpXC - mWC, *mpYC - mHC);
	glVertex2f(*mpXC + mWC, *mpYC - mHC);
	glVertex2f(*mpXC + mWC, *mpYC + mHC);
	glVertex2f(*mpXC - mWC, *mpYC + mHC);
	glEnd();
}