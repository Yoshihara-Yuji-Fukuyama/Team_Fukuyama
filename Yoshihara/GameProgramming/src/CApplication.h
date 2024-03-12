#pragma once
#include "CRectangle.h"
#include "CTexture.h"
#include "CCharacter.h"
#include "CTaskManager.h"
#include "CGame.h"

class CApplication
{

public:
	//ˆê“x‚¾‚¯ŒÄ‚Î‚ê‚é
	void Start();
	//1•bŠÔ‚É60‰ñŒÄ‚Î‚ê‚é
	void Update();

private:
	CGame* mpGame;

};