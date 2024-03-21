#pragma once

#include "CCharacter.h"
#include "CInput.h"
#include "CCollider.h"
#include "CAnimation.h"
#include "CAttack.h"
#include "CShadow.h"

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

	//死亡処理
	void Death();

	/// <summary>
    /// 衝突判定
    /// </summary>
    /// <param name="m">コライダ1</param>
    /// <param name="o">コライダ2</param>
	void Collision(CCollider* m, CCollider* o);

	//アニメーションを設定
	void SetAnimation();

	//isMoveXを取得
	bool GetMoveX();
	//mVxを取得
	float GetmVx();
	//mVxを設定
	void SetmVx();

	/// <summary>
	/// HPを回復する
	/// </summary>
	/// <param name="heal">回復割合</param>
	void HealHp(float heal);
	//ジャンプアップ量を得る
	float GetJumpPower();
	//攻撃力アップ量を得る
	int GetAttackPower();
	//強化の値を上昇
	void SetJumpPower();
	void SetDeffensePower();
	void SetAttackPower();
	void SetAttackNumPower();
	void SetSpeedPower();

	//staticメソッドの宣言
	static CPlayer* GetInstance();

	static CTexture* GetTexture();

	static void DeleteInstance();



private:
	//強化系の効果
	float mJumpPower;
	int mDeffensePower;
	int mAttackPower;
	int mAttackNumPower;
	float mSpeedPower;

	CInput mInput;
	CShadow* mpShadow;

	EAttackPhase mAttackPhase;
	EAttackPhase mAttackPhaseNext;

	bool isClick;

	//体のコライダ
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