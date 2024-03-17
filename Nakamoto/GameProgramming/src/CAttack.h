#pragma once
#include "CCharacter.h"
#include "CCollider.h"
#include "CPlayer.h"

class CAttack :public CCharacter
{
public:
	/// <summary>
	/// 攻撃判定の設定
	/// </summary>
	/// <param name="p">親クラス</param>
	/// <param name="x">X座標のアドレス</param>
	/// <param name="y">Y座標のアドレス</param>
	/// <param name="z">Z座標のアドレス</param>
	/// <param name="mvx">Xの移動方向</param>
	CAttack(CCharacter* p, float* x, float* y, float* z, float mvx);

	//更新
	void Update();

	/// <summary>
	/// 衝突判定
	/// </summary>
	/// <param name="m">コライダ1</param>
	/// <param name="o">コライダ２</param>
	void Collision(CCharacter* m, CCharacter* o);

	//描画(無いとエラーになる)
	void Render();

private:
	CCollider mCollider;
	int mLife;
};