#pragma once
#include "CCharacter.h"
#include "CCollider.h"
#include "CShadow.h"

class CHeal :public CCharacter
{
public:
	CHeal();
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="x">X座標</param>
	/// <param name="y">Y座標</param>
	/// <param name="texture">テクスチャのポインタ</param>
	CHeal(float x, float y, CTexture* texture);
	//デストラクタ
	~CHeal();

	void Update();
	/// <summary>
    /// 衝突判定
    /// </summary>
    /// <param name="m">コライダ1</param>
    /// <param name="o">コライダ2</param>
	void Collision(CCollider* m, CCollider* o);

	//staticメソッドの宣言
	static CTexture* GetTexture();
private:
	CShadow* mpShadow;
	//体のコライダ
	CCollider mCollider;

	//static変数の宣言
	static CTexture mTexture;
};
