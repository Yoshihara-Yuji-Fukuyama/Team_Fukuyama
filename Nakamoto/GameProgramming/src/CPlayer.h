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

	/// <summary>
	/// �Փ˔���
	/// </summary>
	/// <param name="m">�R���C�_1</param>
	/// <param name="o">�R���C�_2</param>
	void Collision(CCollider* m, CCollider* o);

	//���S����
	void Death();

	//�A�j���[�V������ݒ�
	void SetAnimation();

	//static���\�b�h�̐錾
	static CPlayer* GetInstance();

	static CTexture* GetTexture();

private:
	CInput mInput;

	EAttackPhase mAttackPhase;
	EAttackPhase mAttackPhaseNext;

	bool isClick;

	//�R���C�_
	CCollider mCollider;
	//�R���C�_���o�Ă��邩
	bool isCollider;

	//���G�J�E���g
	int mInvincible;

	//�U���̔ԍ�
	int mAttackNumber;

	//static�ϐ��̐錾
	static CPlayer* mpInstance;//�v���C���[�̃C���X�^���X

	static CTexture mTexture;
};