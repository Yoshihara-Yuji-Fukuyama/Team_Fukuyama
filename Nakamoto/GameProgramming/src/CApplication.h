#pragma once
#include "CRectangle.h"
#include "CTexture.h"
#include "CPlayer.h"

class CApplication
{

public:
	//ˆê“x‚¾‚¯ŒÄ‚Î‚ê‚é
	void Start();
	//1•bŠÔ‚É60‰ñŒÄ‚Î‚ê‚é
	void Update();
private:
	CRectangle mRectangle;
	CTexture mTexture;
	CPlayer mPlayer;
};