#pragma once

#include "CCharacter.h"
#include "CInput.h"

class CPlayer : public CCharacter
{
public:
	//コンストラクタ
	CPlayer();
	//デストラクタ
	~CPlayer();
	//更新処理
	void Update();

private:
	CInput mInput;
	float mJump;		//ジャンプ距離
	float mVx, mVy;
};