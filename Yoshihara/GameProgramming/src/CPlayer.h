#pragma once

#include "CCharacter.h"
#include "CInput.h"
#include "CCollider.h"
#include "CAnimation.h"
#include "CAttack.h"

class CPlayer : public CCharacter, public CAnimation
{
public:
	//�U���i�K
	enum class EAttackPhase
	{
		Attack0,//�U�����Ă��Ȃ�
		Attack1,//��i�K��
		Attack2,//��i�K��
		Attack3//�O�i�K��
	};

	//�f�t�H���g�R���X�g���N�^
	CPlayer();
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="x">X���W</param>
	/// <param name="y">Y���W</param>
	/// <param name="w">��</param>
	/// <param name="h">����</param>
	/// <param name="hp">HP</param>
	CPlayer(float x, float y, float w, float h, int hp);
	//�f�X�g���N�^
	~CPlayer();
	//�X�V����
	void Update() override;

	//�ړ�����
	void Move();

	//�U������
	void Attack();

	//���S����
	void Death();

	//�A�j���[�V������ݒ�
	void SetAnimation();

	//isMoveX���擾
	bool GetMoveX();
	//mVx���擾
	float GetmVx();

	//static���\�b�h�̐錾
	static CPlayer* GetInstance();

	static CTexture* GetTexture();

private:
	CInput mInput;

	EAttackPhase mAttackPhase;
	EAttackPhase mAttackPhaseNext;

	bool isClick;

	//�̂̃R���C�_
	CCollider mCollider;
	//�U���̃R���C�_
	//CCollider mACollider;

	//static�ϐ��̐錾
	static CPlayer* mpInstance;//�v���C���[�̃C���X�^���X

	static CTexture mTexture;
};