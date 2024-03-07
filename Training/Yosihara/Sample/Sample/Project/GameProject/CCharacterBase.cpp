#include "CCharacterBase.h"

//コンストラクタ
CCharacterBase::CCharacterBase(const CVector2D& pos,int hp)
	:CObjectBase(pos)
	, mHp(hp)
	, mIsDeath(false)
{

}
//デストラクタ
CCharacterBase::~CCharacterBase()
{

}

//ダメージを受ける
void CCharacterBase::TakeDamage(int damage)
{
	//すでにHPが0であればダメージ処理を実行しない
	if (mHp <= 0)return;
	//残りHPからダメージ分減算
	mHp -= damage;
	//残りHPが0であれば死亡処理
	if (mHp <= 0)
	{
		Death();
	}
}

//死亡したときの処理
void CCharacterBase::Death()
{
	mIsDeath = true;//死亡フラグを立てる
}