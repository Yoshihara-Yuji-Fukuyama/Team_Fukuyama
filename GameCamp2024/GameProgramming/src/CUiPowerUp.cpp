#include "CUiPowerUp.h"
#include "CPlayer.h"
#include <stdlib.h>
#include "CUiTexture.h"

#define TEX_JUMP_UP 0,120,120,0 //ジャンプ力
#define TEX_DEFENSE_UP 120,240,120,0 //防御力
#define TEX_ATTACK_UP 360,240,120,0 //攻撃力
#define TEX_ATTACK_NUM_UP 0,120,240,120 //攻撃段階増加
#define TEX_SPEED_UP 120,240,240,120 //移動速度上昇

#define TEXTURE_YWH 560,100,100 //y,w,h
#define ITEM_ICON 25,25 //w,h

#define JUMP_MAX 3//ジャンプ強化の上限
#define DEFENSE_MAX 3//防御強化の上限
#define ATTACK_MAX 5//攻撃強化の上限
#define ATTACK_NUM_MAX 2//攻撃段階増加の上限
#define SPEED_MAX 3//移動速度強化の上限

#define ITEM_POSX 480

//static変数の定義
CUiPowerUp* CUiPowerUp::mpInstance1;
CUiPowerUp* CUiPowerUp::mpInstance2;
CUiPowerUp* CUiPowerUp::mpInstance3;
CTexture CUiPowerUp::mTexture;
//すでに選択されているかどうか
bool CUiPowerUp::isJumpUp;
bool CUiPowerUp::isDefenseUp;
bool CUiPowerUp::isAttackUp;
bool CUiPowerUp::isAttackNumUp;
bool CUiPowerUp::isSpeedUp;
//強化した回数
int CUiPowerUp::mJumpMax;
int CUiPowerUp::mDefenseMax;
int CUiPowerUp::mAttackMax;
int CUiPowerUp::mAttackNumMax;
int CUiPowerUp::mSpeedMax;
//最大強化のアイテム数
int CUiPowerUp::mMaxItemNum;

//staticメソッドの定義
CUiPowerUp* CUiPowerUp::GetInstance1()
{
	return mpInstance1;
}
CUiPowerUp* CUiPowerUp::GetInstance2()
{
	return mpInstance2;
}
CUiPowerUp* CUiPowerUp::GetInstance3()
{
	return mpInstance3;
}
void CUiPowerUp::SetMaxDefault()
{
	mJumpMax = 0;
	mDefenseMax = 0;
	mAttackMax = 0;
	mAttackNumMax = 0;
	mSpeedMax = 0;
}

//インスタンスの削除
void CUiPowerUp::DeleteInstance()
{
	delete mpInstance1;
	delete mpInstance2;
	delete mpInstance3;
	mpInstance1 = nullptr;
	mpInstance2 = nullptr;
	mpInstance3 = nullptr;
	isJumpUp = false;
	isDefenseUp = false;
	isAttackUp = false;
	isAttackNumUp = false;
	isSpeedUp = false;
}

CTexture* CUiPowerUp::GetTexture()
{
	return &mTexture;
}

int CUiPowerUp::GetMaxItem()
{
	mMaxItemNum = 0;
	if (mJumpMax >= JUMP_MAX)
	{
		mMaxItemNum++;
	}
	if (mDefenseMax >= DEFENSE_MAX)
	{
		mMaxItemNum++;
	}
	if (mAttackMax >= ATTACK_MAX)
	{
		mMaxItemNum++;
	}
	if (mAttackNumMax >= ATTACK_NUM_MAX)
	{
		mMaxItemNum++;
	}
	if (mSpeedMax >= SPEED_MAX)
	{
		mMaxItemNum++;
	}
	return mMaxItemNum;
}

CUiPowerUp::CUiPowerUp()
	:CCharacter((int)CTaskPriority::UI)
{
}

CUiPowerUp::CUiPowerUp(float x, int num)
	: CUiPowerUp()
{

	Set(x, TEXTURE_YWH);

	bool isSelect = false;
	while (isSelect == false)
	{
		int Select = rand();//ランダムな数字

        //5の倍数なら
		if (Select % 5 == 0)
		{
			if (isJumpUp == false && mJumpMax < JUMP_MAX)
			{
				Texture(GetTexture(), TEX_JUMP_UP);
				isJumpUp = true;
				isSelect = true;
				mItem = EItem::JumpUp;
			}
		}
		//上記以外かつ4の倍数なら
		else if (Select % 4 == 0)
		{
			if (isDefenseUp == false && mDefenseMax < DEFENSE_MAX)
			{
				Texture(GetTexture(), TEX_DEFENSE_UP);
				isDefenseUp = true;
				isSelect = true;
				mItem = EItem::DefenseUp;
			}
		}
		//上記以外かつ3の倍数なら
		else if (Select % 3 == 0)
		{
			if (isAttackUp == false && mAttackMax < ATTACK_MAX)
			{
				Texture(GetTexture(), TEX_ATTACK_UP);
				isAttackUp = true;
				isSelect = true;
				mItem = EItem::AttackUp;
			}
		}
		//上記以外かつ2の倍数なら
		else if (Select % 2 == 0)
		{
			if (isAttackNumUp == false && mAttackNumMax < ATTACK_NUM_MAX)
			{
				Texture(GetTexture(), TEX_ATTACK_NUM_UP);
				isAttackNumUp = true;
				isSelect = true;
				mItem = EItem::AttackNumUp;
			}
		}
		//それ以外なら
		else
		{
			if (isSpeedUp == false && mSpeedMax < SPEED_MAX)
			{
				Texture(GetTexture(), TEX_SPEED_UP);
				isSpeedUp = true;
				isSelect = true;
				mItem = EItem::SpeedUp;
			}
		}
	}

	if (num == 1)
	{
		mpInstance1 = this;
		//最大強化のアイテムが最大種類－2個未満なら選択肢3を生成
		if (GetMaxItem() < ITEM_NUM - 2)
		{
			new CUiPowerUp(GetX() + ITEM_POSX * 2, 3);
		}

	}
	else if (num == 2)
	{
		mpInstance2 = this;
		//最大強化のアイテムが最大種類－1個未満なら選択肢1を生成
		if (GetMaxItem() < ITEM_NUM - 1)
		{
			new CUiPowerUp(GetX() - ITEM_POSX, 1);
		}
	}
	else if (num == 3)
	{
		mpInstance3 = this;
	}
}

CUiPowerUp::EItem CUiPowerUp::GetItem()
{
	return mItem;
}

void CUiPowerUp::PowerUp()
{
	EItem getItem;
	if (mInput.Key('1'))
	{
		getItem = mpInstance1->GetItem();
	}
	else if (mInput.Key('2'))
	{
		getItem = mpInstance2->GetItem();
	}
	else if (mInput.Key('3'))
	{
		getItem = mpInstance3->GetItem();
	}

	//ジャンプ強化
	if (getItem == EItem::JumpUp)
	{
		CPlayer::GetInstance()->SetJumpPower();
		mJumpMax++;
		new CUiTexture(ITEM_ICON, CUiTexture::EUiType::Item, TEX_JUMP_UP);
	}
	//防御強化
	else if (getItem == EItem::DefenseUp)
	{
		CPlayer::GetInstance()->SetDeffensePower();
		mDefenseMax++;
		new CUiTexture(ITEM_ICON, CUiTexture::EUiType::Item, TEX_DEFENSE_UP);
	}
	//攻撃強化
	else if (getItem == EItem::AttackUp)
	{
		CPlayer::GetInstance()->SetAttackPower();
		mAttackMax++;
		new CUiTexture(ITEM_ICON, CUiTexture::EUiType::Item, TEX_ATTACK_UP);
	}
	//攻撃段階増加
	else if (getItem == EItem::AttackNumUp)
	{
		CPlayer::GetInstance()->SetAttackNumPower();
		mAttackNumMax++;
		new CUiTexture(ITEM_ICON, CUiTexture::EUiType::Item, TEX_ATTACK_NUM_UP);
	}
	//移動速度上昇
	else
	{
		CPlayer::GetInstance()->SetSpeedPower();
		mSpeedMax++;
		new CUiTexture(ITEM_ICON, CUiTexture::EUiType::Item, TEX_SPEED_UP);
	}
}
