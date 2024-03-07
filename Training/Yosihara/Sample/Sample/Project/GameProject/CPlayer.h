#pragma once
#include "CCharacterBase.h"

class CPlayer :public CCharacterBase
{
//アクセス修飾子
//自分以外の外部からアクセスし放題
public:
	//コンストラクタ
	CPlayer();
	//デストラクタ
	~CPlayer();

	//死亡した時の処理
	void Death() override;

	//更新処理
	void Update() override;
	//描画処理
	void Render() override;

//自分自身のクラスしかアクセスできない
//メンバ変数は基本private
private:
	TexAnimData* mpAnimData;//アニメーションのデータ
	CImage* mpImage;//プレイヤーの画像

};
