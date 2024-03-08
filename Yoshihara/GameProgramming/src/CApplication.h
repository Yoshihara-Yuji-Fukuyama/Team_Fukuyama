#pragma once
#include "CRectangle.h"
#include "CTexture.h"
#include "CCharacter.h"
#include "CTaskManager.h"
#include "CGame.h"

class CApplication
{

public:
	void Start();

	void Update();

private:
	CGame* mpGame;

};