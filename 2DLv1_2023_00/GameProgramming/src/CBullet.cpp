#include "CBullet.h"
#include "CApplication.h"


//�e�̓���
void CBullet::Update()
{
	//�X�e�[�^�X�����[�u�̏ꍇ�����A��ʂ̒[�ɍs���Ƌt����o��
	if (mState == EState::EMOVE)
	{
		float y = Y() + H();
		if (y > 620.0f)
		{
			y = 0.0f;
		}
		Y(y);
	}
}



//�����蔻��
bool CBullet::Collision(CRectangle* rect)
{
	if (CRectangle::Collision(rect))//���������ꍇ�X�g�b�v�ɂ���
	{
		mState = EState::ESTOP;
		return true;
	}
	return false;
}



//�X�e�[�^�X���X�g�b�v�ɂ���
CBullet::CBullet()
{
	mState = EState::ESTOP;
}



//�e�̐ݒ�
CBullet::CBullet(float x, float y, float w, float h,
	float l, float r, float b, float t, CTexture* pt)
{
	Set(x, y, w, h);

	Texture(pt, l, r, b, t);

	mState = EState::EMOVE;

	mTag = ETag::EBULLET;
}



void CBullet::Collision()
{
	CApplication::CharacterManager()->Collision(this);
}


//�e�̓����蔻��
void CBullet::Collision(CCharacter* m, CCharacter* o)
{
	switch (o->Tag())
	{

		//���̒e�ɓ��������ꍇ
	case ETag::EBULLET:

		break;


		//�e�ȊO�ɓ��������ꍇ
	default:

		if (CRectangle::Collision(o))
		{
			mState = EState::ESTOP;

			mEnabled = false;
		}

	}
}