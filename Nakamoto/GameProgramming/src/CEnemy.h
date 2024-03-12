#pragma once
#include "CCharacter.h"
#include "CCollider.h"

class CEnemy :public CCharacter
{
public:
	void Update() override;

	//デフォルトコンストラクタ
	CEnemy();
	/// <summary>
	/// 敵のコンストラクタ
	/// </summary>
	/// <param name="x">X座標</param>
	/// <param name="y">Y座標</param>
	/// <param name="w">幅</param>
	/// <param name="h">高さ</param>
	CEnemy(float x, float y, float w, float h);

	void Collision(CCollider* m, CCollider* o);

	//staticメソッドの宣言
	static CTexture* GetTexture();

private:
	//コライダ
	CCollider mColider;
	//static変数の宣言
	static CTexture mTexture;
};