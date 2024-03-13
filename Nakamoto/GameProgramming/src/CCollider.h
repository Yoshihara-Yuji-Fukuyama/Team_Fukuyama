#pragma once
#include "CCharacter.h"

class CCollisionManager;

class CCollider :public CCharacter
{
	friend CCollisionManager;
public:
	//デフォルトコンストラクタ
	CCollider();
	//デストラクタ
	~CCollider();

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="parent">親</param>
	/// <param name="x">X座標ポインタ</param>
	/// <param name="y">Y座標ポインタ</param>
	/// <param name="w">幅</param>
	/// <param name="h">高さ</param>
	CCollider(CCharacter* parent, 
		float *px, float *py, float w, float h);
	//親ポインタの取得
	CCharacter* GetParent();

	//描画
	void Render();

	//攻撃時の当たり判定生成
	void AttackCollider(CCharacter* parent, float x,float y,float w,float h);

	/// <summary>
	/// 衝突判定(めり込まない処理)
	/// </summary>
	/// <param name="m">コライダ1</param>
	/// <param name="o">コライダの2</param>
	/// <param name="ax">Xの修正値</param>
	/// <param name="ay">Yの修正値</param>
	/// <returns>true(衝突している) false(衝突していない)</returns>
	static bool Collision(CCollider* m, CCollider* o,float *ax,float *ay);

protected:
	CCharacter* mpParent;	//親

	float* mpX, * mpY, mH, mW;	
};