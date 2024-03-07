#pragma once
#include "CRectangle.h"
#include "CTexture.h"
#include "CCharacter.h"
#include "CEnemy.h"
#include "CTaskManager.h"
#include "CGame.h"

//定数の定義
#define TEXTURE "ge-mu.png"

class CApplication
{

public:
	void Start();

	void Update();

	//staticメソッドの宣言
	static CTexture* GetTexture();

	static CTaskManager* GetTaskManager();

private:
	CEnemy* mpEnemy;

	CGame* mpGame;

	//static変数の宣言
	static CTexture mTexture;

	static CTaskManager mTaskManager;
};