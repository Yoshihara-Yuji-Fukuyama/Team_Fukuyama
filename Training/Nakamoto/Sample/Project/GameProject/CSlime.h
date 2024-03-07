#pragma once
#include "CharaBase.h"

class CSlime :public CharaBase
{
	//アクセス修飾子
//自分以外の外部からアクセスし放題
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="type">スライムの種類</param>
	/// <param name="pos">初期位置</param>
	CSlime(int type ,const CVector2D &pos);
	//デストラクタ
	~CSlime() ;

	//更新処理
	void Update() override;
	//描画処理
	void Render() override;

	//自分自身のクラスしかアクセスできない
	//メンバ変数は基本private
private:
	TexAnimData* mpAnimData;	//アニメーションのデータ
	CImage* mpImage;	//画像
	int mType;			//スライムの種類

};