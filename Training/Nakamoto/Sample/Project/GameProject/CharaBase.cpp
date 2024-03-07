#include "CharaBase.h"

//�R���X�g���N�^
CharaBase::CharaBase(const CVector2D& pos)
	:ObjectBase(pos)
	,mHp(100)
	,mIsDeath(false)
{

}

//�f�X�g���N�^
CharaBase::~CharaBase()
{

}

//�_���[�W���󂯂�
void CharaBase::TakeDamage(int damage)
{
	//����HP��0�ł���΁A�_���[�W���������s���Ȃ�
	if (mHp <= 0) return;

	//�c��HP����_���[�W�����Z
	mHp -= damage;
	//�c��HP��0�ł���΁A
	if (mHp <= 0)
	{
		//���S����
		Death();
	}
}

//���S�����Ƃ��̏���
void CharaBase::Death()
{
	//���S�t���O�𗧂Ă�
	mIsDeath = true;
}