#pragma once
#include "CCharacter.h"
#include "CCollider.h"
#include "CPlayer.h"

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
	/// <param name="mvx">X�̈ړ�����</param>
	/// <param name="attackNumber">�U���i�K</param>
	CAttack(CCharacter* parent, float* x, float* y, float* z, float mvx, int attackNumber);

	//�X�V
	void Update();

	//�`��(�����ƃG���[�ɂȂ�)
	void Render();

private:
	CCollider mCollider;
	int mLife;
};