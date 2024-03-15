#pragma once
#include "CCharacter.h"
#include "CCollider.h"

class CAttack :public CCharacter
{
public:
	/// <summary>
	/// �U������̐ݒ�
	/// </summary>
	/// <param name="p">�e�N���X</param>
	/// <param name="x">X���W�̃A�h���X</param>
	/// <param name="y">Y���W�̃A�h���X</param>
	/// <param name="z">Z���W�̃A�h���X</param>
	CAttack(CCharacter* p,float *x,float *y,float *z ,float mvx);

	//�X�V
	void Update();

	//�Փ˔���
	void Collision();
	/// <summary>
	/// �Փ˔���
	/// </summary>
	/// <param name="m">�R���C�_1</param>
	/// <param name="o">�R���C�_�Q</param>
	void Collision(CCharacter* m, CCharacter* o);

	//�`��(�����ƃG���[�ɂȂ�)
	void Render();

private:
	CCollider mCollider;
	int mLife;
};