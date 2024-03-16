#pragma once
#include "CCharacter.h"

class CCollisionManager;

class CCollider :public CRectangle,public CTask
{
	friend CCollisionManager;
public:
	//�R���C�_�̃^�C�v
	enum class EType
	{
		EPLAYER,	//�v���C���[�̃R���C�_
		EPATTACK1,	//�v���C���[�̍U��1
		EPATTACK2,	//�v���C���[�̍U��2
		EPATTACK3,	//�v���C���[�̍U��3

		ESLIME,     //�X���C���̃R���C�_
		ESATTACK,	//�X���C���̍U��

		EONI,		//�S�̃R���C�_
		EOATTACK	//�S�̍U��
	};



	//�f�t�H���g�R���X�g���N�^
	CCollider();
	//�f�X�g���N�^
	~CCollider();

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="parent">�e</param>
	/// <param name="x">X���W�|�C���^</param>
	/// <param name="y">Y���W�|�C���^</param>
	/// <param name="w">��</param>
	/// <param name="h">����</param>
	CCollider(CCharacter* parent, 
		float *px, float *py,float* z, float w, float h , bool attack = false);
	//�e�|�C���^�̎擾
	CCharacter* GetParent();

	//�`��
	void Render();

	//�U�����̓����蔻�萶��
	void AttackCollider(CCharacter* parent, float x,float y,float w,float h);

	/// <summary>
	/// �Փ˔���(�߂荞�܂Ȃ�����)
	/// </summary>
	/// <param name="m">�R���C�_1</param>
	/// <param name="o">�R���C�_��2</param>
	/// <param name="ax">X�̏C���l</param>
	/// <param name="ay">Y�̏C���l</param>
	/// <returns>true(�Փ˂��Ă���) false(�Փ˂��Ă��Ȃ�)</returns>
	static bool Collision(CCollider* m, CCollider* o,float *ax,float *ay);

protected:
	CCharacter* mpParent;	//�e

	float* mpX, * mpY, * mLeg;
	float mCH;	//�R���C�_�̍���
	float mCW;	//�R���C�_�̕�

};