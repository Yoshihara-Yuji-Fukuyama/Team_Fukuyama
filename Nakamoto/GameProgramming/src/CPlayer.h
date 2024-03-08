#pragma once

#include "CCharacter.h"
#include "CInput.h"

class CPlayer : public CCharacter
{
public:
	//�R���X�g���N�^
	CPlayer();
	//�f�X�g���N�^
	~CPlayer();
	//�X�V����
	void Update();

private:
	CInput mInput;
	float mJump;		//�W�����v����
	float mVx, mVy;
};