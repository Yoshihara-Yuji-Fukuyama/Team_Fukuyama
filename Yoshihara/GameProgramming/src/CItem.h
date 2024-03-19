#pragma once
#include "CCharacter.h"
#include "CCollider.h"

class CItem :public CCharacter
{
public:
	CItem();
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="x">X座標</param>
	/// <param name="y">Y座標</param>
	/// <param name="w">幅</param>
	/// <param name="h">高さ</param>
	/// <param name="texture">テクスチャのポインタ</param>
	CItem(float x, float y, float w, float h, CTexture* texture);

	/// <summary>
    /// 衝突判定
    /// </summary>
    /// <param name="m">コライダ1</param>
    /// <param name="o">コライダ2</param>
	void Collision(CCollider* m, CCollider* o);

	//staticメソッドの宣言
	static CTexture* GetTexture();
private:
	//体のコライダ
	CCollider mCollider;

	//static変数の宣言
	static CTexture mTexture;
};
