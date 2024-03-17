#pragma once
#include "CCharacter.h"
#include "CEnemy.h"

class CCollisionManager;

class CCollider :public CRectangle,public CTask
{
	friend CCollisionManager;
public:
	//コライダのタイプ
	enum class EColliderType
	{
		EPLAYER,	//プレイヤーのコライダ
		EPATTACK1,	//プレイヤーの攻撃1
		EPATTACK2,	//プレイヤーの攻撃2
		EPATTACK3,	//プレイヤーの攻撃3

		ESLIME,     //スライムのコライダ
		ESATTACK,	//スライムの攻撃

		EONI,		//鬼のコライダ
		EOATTACK	//鬼の攻撃
	};

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
	/// <param name="cType">コライダのタイプ</param>
	/// <param name="attack">攻撃しているか</param>
	CCollider(CCharacter* parent, 
		float *px, float *py,float* z, float w, float h, EColliderType cType, bool attack = false);
	//親ポインタの取得
	CCharacter* GetParent();

	//描画
	void Render();

	//コライダのタイプを取得
	CCollider::EColliderType GetCType();

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
	//コライダのタイプ
	EColliderType mColliderType;	

	float* mpX, * mpY, * mLeg;
	float mCH;	//コライダの高さ
	float mCW;	//コライダの幅
};