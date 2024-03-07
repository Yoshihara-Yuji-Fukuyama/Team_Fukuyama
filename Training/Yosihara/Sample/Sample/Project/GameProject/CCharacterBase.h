#pragma once
#include "CObjectBase.h"

class CCharacterBase :public CObjectBase
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="pos">初期位置</param>
	/// <param name="hp">初期HP</param>
	CCharacterBase(const CVector2D& pos,int hp);
	//デストラクタ
	virtual ~CCharacterBase();
	/// <summary>
	/// ダメージを受ける
	/// </summary>
	/// <param name="damage">受けるダメージ量</param>
	void TakeDamage(int damage);

	//死亡したときの処理
	virtual void Death();

protected:
	int mHp;//キャラクターの残りHP
	bool mIsDeath;//キャラクターが死んでいるかどうか
};
