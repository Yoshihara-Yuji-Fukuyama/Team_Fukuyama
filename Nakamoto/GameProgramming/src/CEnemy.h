#pragma once
#include "CCharacter.h"
#include "CAnimation.h"
#include "CCollider.h"
#include "CAttack.h"

class CEnemy :public CCharacter, public CAnimation
{
public:
	enum class EEnemyType//敵タイプ
	{
		Slime,      //スライム
		Oni,        //鬼
	};

	//更新処理
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
	/// <param name="hp">HP</param>
	/// <param name="enemyType">敵の種類</param>
	CEnemy(float x, float y, float w, float h, int hp, EEnemyType enemyType);

	//デストラクタ
	~CEnemy();

	//移動処理
	void Move();

	//アニメーションを設定
	void SetAnimation();

	void Attack();

	//死亡処理
	void Death();

	//敵のタイプの取得
	CEnemy::EEnemyType GetEnemyType();

	/// <summary>
	/// 衝突判定
	/// </summary>
	/// <param name="m">コライダ1</param>
	/// <param name="o">コライダ2</param>
	void Collision(CCollider* m, CCollider* o);

	//staticメソッドの宣言
	static CTexture* GetTextureSlime();

	static CTexture* GetTextureOni();

private:
	//敵の種類
	EEnemyType mEnemyType;
	//コライダ
	CCollider mCollider;

	//フレームカウンタ
	int mFrame;
	//ランダム
	int RandomX;
	int RandomY;
	int RandomTiming;

	bool isCollider;

	//無敵カウント
	int mInvincible;

	//static変数の宣言
	static CTexture mTextureSlime;

	static CTexture mTextureOni;
};