#pragma once
#include "CCharacter.h"

class CCollisionManager;

class CCollider :public CRectangle, public CTask
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
	/// <param name="parent">親クラス</param>
	/// <param name="x">X座標</param>
	/// <param name="y">Y座標</param>
	/// <param name="w">幅</param>
	/// <param name="h">高さ</param>
	CCollider(CCharacter* parent,
		float &x, float &y, float w, float h);

	/// <summary>
	/// 衝突処理
	/// </summary>
	/// <param name="m">コライダ1</param>
	/// <param name="o">コライダ2</param>
	/// <param name="ax">X座標の調整ポインタ</param>
	/// <param name="ay">Y座標の調整ポインタ</param>
	/// <returns>true(衝突している) false(衝突していない)</returns>
	static bool Collision(CCollider* m, CCollider* o, float* ax, float* ay);

	//優先度の変更
	virtual void ChangePriority();
	//優先度の変更
	void ChanegePriority(int priority);

	//親クラスの取得
	CCharacter* GetParent();
	//描画
	void Render();

protected:
	CCharacter* mpParent;	//親クラス
	float *mpXC;	//コライダーのX座標
	float *mpYC;	//コライダーのY座標
	float mHC;  //コライダーの高さ
	float mWC;	//コライダーの幅

};
