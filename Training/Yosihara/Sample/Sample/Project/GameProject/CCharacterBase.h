#pragma once
#include "CObjectBase.h"

class CCharacterBase :public CObjectBase
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="pos">�����ʒu</param>
	/// <param name="hp">����HP</param>
	CCharacterBase(const CVector2D& pos,int hp);
	//�f�X�g���N�^
	virtual ~CCharacterBase();
	/// <summary>
	/// �_���[�W���󂯂�
	/// </summary>
	/// <param name="damage">�󂯂�_���[�W��</param>
	void TakeDamage(int damage);

	//���S�����Ƃ��̏���
	virtual void Death();

protected:
	int mHp;//�L�����N�^�[�̎c��HP
	bool mIsDeath;//�L�����N�^�[������ł��邩�ǂ���
};
