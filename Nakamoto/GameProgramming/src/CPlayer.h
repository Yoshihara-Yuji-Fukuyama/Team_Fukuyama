#pragma once

#include "CCharacter.h"
#include "CInput.h"
#include "CCollider.h"

class CPlayer : public CCharacter
{
public:
	//デフォルトコンストラクタ
	CPlayer();
	//コンストラクタ
	CPlayer(float x, float y, float w, float h);
	//デストラクタ
	~CPlayer();
	//更新処理
	void Update();
	
	/// <summary>
	/// 衝突処理
	/// </summary>
	/// <param name="m">コライダ1</param>
	/// <param name="o">コライダ2</param>
	void Collision(CCollider* m,CCollider* o);
	//優先度の変更
	void ChengePriority();

	//staticメソッドの宣言
	static CTexture* GetTexture();

private:
	CInput mInput;
	float mJump;		//ジャンプ距離

	CCollider mCollider;	//コライダー

	//static変数の宣言
	static CTexture mTexture;
};