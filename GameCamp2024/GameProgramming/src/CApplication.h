#pragma once
#include "CRectangle.h"
#include "CTexture.h"
#include "CCharacter.h"
#include "CTaskManager.h"
#include "CGame.h"

class CApplication
{

public:
	//一度だけ呼ばれる
	void Start();
	//1秒間に60回呼ばれる
	void Update();

private:
	CGame* mpGame;

};