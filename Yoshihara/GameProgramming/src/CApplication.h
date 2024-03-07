#pragma once
#include "CRectangle.h"
#include "CTexture.h"
#include "CCharacter.h"
#include "CEnemy.h"
#include "CTaskManager.h"
#include "CGame.h"

//�萔�̒�`
#define TEXTURE "ge-mu.png"

class CApplication
{

public:
	void Start();

	void Update();

	//static���\�b�h�̐錾
	static CTexture* GetTexture();

	static CTaskManager* GetTaskManager();

private:
	CEnemy* mpEnemy;

	CGame* mpGame;

	//static�ϐ��̐錾
	static CTexture mTexture;

	static CTaskManager mTaskManager;
};