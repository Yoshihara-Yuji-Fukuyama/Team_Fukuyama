#pragma once
#include "CCharacter.h"

class CCollisionManager;

class CCollider :public CCharacter
{
	friend CCollisionManager;
public:
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
		float *px, float *py, float w, float h);
	//�e�|�C���^�̎擾
	CCharacter* GetParent();

	//�`��
	void Render();

	/// <summary>
	/// �Փ˔���
	/// </summary>
	/// <param name="m">�R���C�_1</param>
	/// <param name="o">�R���C�_2</param>
	/// <returns>true(�Փ˂��Ă���) faulse(�Փ˂��Ă��Ȃ�)</returns>
	static bool Collision(CCollider* m, CCollider* o);
protected:
	CCharacter* mpParent;	//�e

	float* mpX, * mpY, mH, mW;	
};