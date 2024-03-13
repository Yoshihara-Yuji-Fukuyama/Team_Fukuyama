#pragma once

#include "CCharacter.h"
#include "CInput.h"
#include "CCollider.h"
#include "CAnimation.h"

class CPlayer : public CCharacter, public CAnimation
{
public:

	//�f�t�H���g�R���X�g���N�^
	CPlayer();
	//�R���X�g���N�^
	CPlayer(float x, float y, float w, float h);
	//�f�X�g���N�^
	~CPlayer();
	//�X�V����
	void Update() override;

	//�ړ�����
	void Move();

	//���S����
	void Death();

	//�A�j���[�V������ݒ�
	void SetAnimation();
	//�W�����v�A�j���[�V����
	void JumpAnimation();

	//static���\�b�h�̐錾
	static CPlayer* GetInstance();

	static CTexture* GetTexture();

private:
	CInput mInput;
	float mJump;		//�W�����v����

	//�R���C�_
	CCollider mCollider;

	//static�ϐ��̐錾
	static CPlayer* mpInstance;//�v���C���[�̃C���X�^���X

	static CTexture mTexture;
};