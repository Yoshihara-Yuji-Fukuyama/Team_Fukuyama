#pragma once
#include "CCharacter.h"
#include "CEnemy.h"

class CCollisionManager;

class CCollider :public CRectangle,public CTask
{
	friend CCollisionManager;
public:
	//�R���C�_�̃^�C�v
	enum class EColliderType
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
	/// <param name="cType">�R���C�_�̃^�C�v</param>
	/// <param name="attack">�U�����Ă��邩</param>
	CCollider(CCharacter* parent, 
		float *px, float *py,float* z, float w, float h, EColliderType cType, bool attack = false);
	//�e�|�C���^�̎擾
	CCharacter* GetParent();

	//�`��
	void Render();

	//�R���C�_�̃^�C�v���擾
	CCollider::EColliderType GetCType();

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
	//�R���C�_�̃^�C�v
	EColliderType mColliderType;	

	float* mpX, * mpY, * mLeg;
	float mCH;	//�R���C�_�̍���
	float mCW;	//�R���C�_�̕�
};