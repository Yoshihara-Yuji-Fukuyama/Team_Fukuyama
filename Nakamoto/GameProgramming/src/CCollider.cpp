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
bool CCollider::Collision(CCollider* m, CCollider* o)
{
	float x, y;
	if (m->mpX < o->mpX)
		x = o->mpX - m->mpX - m->mW - o->mW;
	else
		x = m->mpX - o->mpX - m->mW - o->mW;
	//0�ȏ�͏Փ˂��Ȃ�
	if (x >= 0.0f)
		return false;

	if (m->mpY < o->mpY)
		y = o->mpY - m->mpY - m->mH - o->mH;
	else
		y = m->mpY - o->mpY - m->mH - o->mH;
	//0�ȏ�͏Փ˂��Ȃ�
	if (y >= 0.0f)
		return false;

	//Y���Z��������
	if (x < y)
	{
		//Y�C���AX��0
		x = 0.0f;
		//��̎�
		if (m->mpY > o->mpY)
			y = -y;
	}
	else
	{
		//X�C���AY��0
		y = 0.0f;
		//��̎�
		if (m->mpX > o->mpX)
			x = -x;
	}
	return true;
}