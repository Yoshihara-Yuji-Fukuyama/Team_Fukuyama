#pragma once
#include "CRectangle.h"
#include "CTexture.h"
#include "CCharacter.h"
#include "CTaskManager.h"
#include "CGame.h"

class CApplication
{

public:
	//��x�����Ă΂��
	void Start();
	//1�b�Ԃ�60��Ă΂��
	void Update();

private:
	CGame* mpGame;

};