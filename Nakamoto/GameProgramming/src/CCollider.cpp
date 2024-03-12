#include "CCollider.h"
#include "CCollisionManager.h"

CCollider::~CCollider()
{
	//�R���W�������X�g����폜
	CCollisionManager::GetInstance()->Remove(this);
}

CCollider::CCollider(CCharacter* parent,
	float* px, float* py, float w, float h)
{
	//�R���W�����}�l�[�W���ɒǉ�
	CCollisionManager::GetInstance()->Add(this);

	//�e�̐ݒ�
	mpParent = parent;
	
	mpX = px;	//X���W
	mpY = py;	//Y���W
	mW = w;		//����
	mH = h;		//��
}

CCharacter* CCollider::GetParent()
{
	return mpParent;
}

void CCollider::Render()
{
	glBegin(GL_QUADS);
	glVertex2f(*mpX - mW, *mpY - mH);
	glVertex2f(*mpX + mW, *mpY - mH);
	glVertex2f(*mpX + mW, *mpY + mH);
	glVertex2f(*mpX - mW, *mpY + mH);
	glEnd();
}

//�Փ˔���
bool CCollider::Collision(CCollider* m, CCollider* o, float *ax, float *ay)
{
	if (*m->mpX < *o->mpX)
		*ax = *o->mpX - *m->mpX - m->mW - o->mW;
	else
		*ax = *m->mpX - *o->mpX - m->mW - o->mW;
	//0�ȏ�͏Փ˂��Ȃ�
	if (*ax >= 0.0f)
		return false;

	if (*m->mpY < *o->mpY)
		*ay = *o->mpY - *m->mpY - m->mH - o->mH;
	else
		*ay = *m->mpY - *o->mpY - m->mH - o->mH;
	//0�ȏ�͏Փ˂��Ȃ�
	if (*ay >= 0.0f)
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