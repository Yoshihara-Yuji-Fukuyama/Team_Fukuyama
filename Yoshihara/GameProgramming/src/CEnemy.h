#pragma once
#include "CCharacter.h"
#include "CCollider.h"
#include "CAnimation.h"
#include "CShadow.h"

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

	void Collision(CCollider* m, CCollider* o);

	//アニメーションを設定
	void SetAnimation();

	//死亡処理
	void Death();

	//staticメソッドの宣言
	static CTexture* GetTextureSlime();

	static CTexture* GetTextureOni();

	//敵の数を取得
	static int GetEnemyCount();
	//敵の数を１加算
	static void PlusEnemyCount();

private:
	CShadow* mpShadow;
	//敵の種類
	EEnemyType mEnemyType;
	//コライダ
	CCollider mColider;
	//フレームカウンタ
	int mFrame;
	//ランダム
	int RandomX;
	int RandomY;
	int RandomTiming;

	//static変数の宣言
	static CTexture mTextureSlime;

	static CTexture mTextureOni;

	static int mEnemyCount;

};