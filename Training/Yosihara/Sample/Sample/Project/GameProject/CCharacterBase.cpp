#include "CCharacterBase.h"

//�R���X�g���N�^
CCharacterBase::CCharacterBase(const CVector2D& pos,int hp)
	:CObjectBase(pos)
	, mHp(hp)
	, mIsDeath(false)
{

}
//�f�X�g���N�^
CCharacterBase::~CCharacterBase()
{

}

//�_���[�W���󂯂�
void CCharacterBase::TakeDamage(int damage)
{
	//���ł�HP��0�ł���΃_���[�W���������s���Ȃ�
	if (mHp <= 0)return;
	//�c��HP����_���[�W�����Z
	mHp -= damage;
	//�c��HP��0�ł���Ύ��S����
	if (mHp <= 0)
	{
		Death();
	}
}

//���S�����Ƃ��̏���
void CCharacterBase::Death()
{
	mIsDeath = true;//���S�t���O�𗧂Ă�
}