#pragma once

#include "CCharacter.h"
#include "CInput.h"
#include "CCollider.h"

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
	void Update();

	//static���\�b�h�̐錾
	static CTexture* GetTexture();

private:
	CInput mInput;
	float mJump;		//�W�����v����

	//�R���C�_
	CCollider mCollider;

	//static�ϐ��̐錾
	static CTexture mTexture;
};