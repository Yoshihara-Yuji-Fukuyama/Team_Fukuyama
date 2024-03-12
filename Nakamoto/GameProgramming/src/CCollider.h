#pragma once
#include "CCharacter.h"

class CCollisionManager;

class CCollider :public CCharacter
{
	friend CCollisionManager;
public:
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

	/// <summary>
	/// 衝突判定
	/// </summary>
	/// <param name="m">コライダ1</param>
	/// <param name="o">コライダ2</param>
	/// <returns>true(衝突している) faulse(衝突していない)</returns>
	static bool Collision(CCollider* m, CCollider* o);
protected:
	CCharacter* mpParent;	//親

	float* mpX, * mpY, mH, mW;	
};