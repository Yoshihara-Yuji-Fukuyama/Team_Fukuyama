#pragma once
#include "CCharacter.h"

class CCollisionManager;

class CCollider :public CRectangle, public CTask
{
	friend CCollisionManager;
public:
	//�f�t�H���g�R���X�g���N�^
	CCollider();
	//�f�X�g���N�^
	~CCollider();

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="parent">�e�N���X</param>
	/// <param name="x">X���W</param>
	/// <param name="y">Y���W</param>
	/// <param name="w">��</param>
	/// <param name="h">����</param>
	CCollider(CCharacter* parent,
		float &x, float &y, float w, float h);

	/// <summary>
	/// �Փˏ���
	/// </summary>
	/// <param name="m">�R���C�_1</param>
	/// <param name="o">�R���C�_2</param>
	/// <param name="ax">X���W�̒����|�C���^</param>
	/// <param name="ay">Y���W�̒����|�C���^</param>
	/// <returns>true(�Փ˂��Ă���) false(�Փ˂��Ă��Ȃ�)</returns>
	static bool Collision(CCollider* m, CCollider* o, float* ax, float* ay);

	//�D��x�̕ύX
	virtual void ChangePriority();
	//�D��x�̕ύX
	void ChanegePriority(int priority);

	//�e�N���X�̎擾
	CCharacter* GetParent();
	//�`��
	void Render();

protected:
	CCharacter* mpParent;	//�e�N���X
	float *mpXC;	//�R���C�_�[��X���W
	float *mpYC;	//�R���C�_�[��Y���W
	float mHC;  //�R���C�_�[�̍���
	float mWC;	//�R���C�_�[�̕�

};
