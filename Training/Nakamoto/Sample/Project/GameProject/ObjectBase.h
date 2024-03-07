#pragma once
#include "CTask.h"

//ゲーム中のオブジェクトのベースクラス
class ObjectBase : public CTask
{
public:
	//コンストラクタ
	ObjectBase(const CVector2D& pos);
	//デストラクタ
    virtual ~ObjectBase();

	/// <summary>
	/// オブジェクトの座標を設定
	/// </summary>
	/// <param name="pos">設定する座標</param>
	void SetPos(const CVector2D& pos);

	/// <summary>
	/// オブジェクトの座標を取得
	/// </summary>
	/// <returns>オブジェクトの座標</returns>
	const CVector2D& GetPos() const;

protected:
	CVector2D mPos;	//オブジェクトの座標
};