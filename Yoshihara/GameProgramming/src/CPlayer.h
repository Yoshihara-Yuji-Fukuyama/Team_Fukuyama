#pragma once

#include "CCharacter.h"
#include "CInput.h"

class CPlayer : public CCharacter
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

	//�ړ��A�j���[�V����
	void MoveAnimation();

	//static���\�b�h�̐錾
	static CPlayer* GetInstance();

	static CTexture* GetTexture();

private:
	CInput mInput;
	float mJump;		//�W�����v����
	bool isMove;        //�ړ����Ă��邩

	//static�ϐ��̐錾
	static CPlayer* mpInstance;//�v���C���[�̃C���X�^���X

	static CTexture mTexture;
};