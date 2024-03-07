#pragma once
#include "CRectangle.h"
#include "CTexture.h"
#include "CPlayer.h"
//タスクリスト
//#include "CTaskManager.h"

class CApplication
{

public:
	//一度だけ呼ばれる
	void Start();
	//1秒間に60回呼ばれる
	void Update();
private:
	CRectangle mRectangle;
	CTexture mTexture;
	CPlayer* mpPlayer;
};