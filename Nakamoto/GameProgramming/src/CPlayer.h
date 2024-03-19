#pragma once

#include "CCharacter.h"
#include "CInput.h"
#include "CCollider.h"
#include "CAnimation.h"
#include "CAttack.h"

class CPlayer : public CCharacter, public CAnimation
{
public:
	//攻撃段階
	enum class EAttackPhase
	{
		Attack0,//攻撃していない
		Attack1,//一段階目
		Attack2,//二段階目
		Attack3//三段階目
	};

	//デフォルトコンストラクタ
	CPlayer();
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="x">X座標</param>
	/// <param name="y">Y座標</param>
	/// <param name="w">幅</param>
	/// <param name="h">高さ</param>
	/// <param name="hp">HP</param>
	CPlayer(float x, float y, float w, float h, int hp);

	//デストラクタ
	~CPlayer();
	//更新処理
	void Update() override;

	//移動入力
	void Move();

	//攻撃処理
	void Attack();

	/// <summary>
	/// 衝突判定
	/// </summary>
	/// <param name="m">コライダ1</param>
	/// <param name="o">コライダ2</param>
	void Collision(CCollider* m, CCollider* o);

	//死亡処理
	void Death();

	//アニメーションを設定
	void SetAnimation();

	//staticメソッドの宣言
	static CPlayer* GetInstance();

	static CTexture* GetTexture();

private:
	CInput mInput;

	EAttackPhase mAttackPhase;
	EAttackPhase mAttackPhaseNext;

	bool isClick;

	//コライダ
	CCollider mCollider;
	//コライダが出ているか
	bool isCollider;

	//無敵カウント
	int mInvincible;

	//攻撃の番号
	int mAttackNumber;

	//static変数の宣言
	static CPlayer* mpInstance;//プレイヤーのインスタンス

	static CTexture mTexture;
};