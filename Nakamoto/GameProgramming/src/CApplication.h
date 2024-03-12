#pragma once
#include "CRectangle.h"
#include "CTexture.h"
#include "CPlayer.h"
#include "CTexture.h"
#include "CCharacter.h"
#include "CTaskManager.h"
#include "CGame.h"
#include "CCharacterManager.h"

//�^�X�N���X�g
//#include "CTaskManager.h"

class CApplication
{

public:
	//��x�����Ă΂��
	void Start();
	//1�b�Ԃ�60��Ă΂��
	void Update();
private:
	CGame* mpGame;

	CCharacterManager mCharacterManager;
};