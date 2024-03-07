#pragma once
#include "CRectangle.h"
#include "CTexture.h"
#include "CPlayer.h"
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
	CRectangle mRectangle;
	CTexture mTexture;
	CPlayer* mpPlayer;
};