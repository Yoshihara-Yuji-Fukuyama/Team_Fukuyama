#pragma once
#include "CTexture.h"
#include "CCharacter.h"
#include "CInput.h"

class CUiPowerUp :public CCharacter
{
public:
	//アイテムの種類
	enum class EItem
	{
		JumpUp,
		DefenseUp,
		AttackUp,
		AttackNumUp,
		SpeedUp,
	};

	CUiPowerUp();
	CUiPowerUp(float x, int num);

	//強化適用
	void PowerUp();

	CUiPowerUp::EItem GetItem();
	//staticメソッドの宣言
	static CUiPowerUp* GetInstance1();
	static CUiPowerUp* GetInstance2();
	static CUiPowerUp* GetInstance3();
	static void DeleteInstance();
	static CTexture* GetTexture();
	static void SetMaxDefault();	//デフォルトに戻す
private:
	CInput mInput;
	EItem mItem;
	//static変数の宣言
	static CUiPowerUp* mpInstance1;
	static CUiPowerUp* mpInstance2;
	static CUiPowerUp* mpInstance3;
	static CTexture mTexture;
	//選ばれたかどうか
	static bool isJumpUp;
	static bool isDefenseUp;
	static bool isAttackUp;
	static bool isAttackNumUp;
	static bool isSpeedUp;
	//強化回数
	static int mJumpMax;
	static int mDefenseMax;
	static int mAttackMax;
	static int mAttackNumMax;
	static int mSpeedMax;
};