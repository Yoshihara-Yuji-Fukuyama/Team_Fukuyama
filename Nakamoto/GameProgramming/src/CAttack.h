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
	/// <param name="attackNumber">攻撃段階</param>
	CAttack(CCharacter* parent, float* x, float* y, float* z, float mvx, int attackNumber);

	//更新
	void Update();

	//描画(無いとエラーになる)
	void Render();

private:
	CCollider mCollider;
	int mLife;
};