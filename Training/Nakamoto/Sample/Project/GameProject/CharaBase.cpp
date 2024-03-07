#include "CharaBase.h"

//コンストラクタ
CharaBase::CharaBase(const CVector2D& pos)
	:ObjectBase(pos)
	,mHp(100)
	,mIsDeath(false)
{

}

//デストラクタ
CharaBase::~CharaBase()
{

}

//ダメージを受ける
void CharaBase::TakeDamage(int damage)
{
	//既にHPが0であれば、ダメージ処理を実行しない
	if (mHp <= 0) return;

	//残りHPからダメージ分減算
	mHp -= damage;
	//残りHPが0であれば、
	if (mHp <= 0)
	{
		//死亡処理
		Death();
	}
}

//死亡したときの処理
void CharaBase::Death()
{
	//死亡フラグを立てる
	mIsDeath = true;
}