#pragma once
#include "CTexture.h"
#include "CRectangle.h"
#include "CTask.h"

//コライダクラスの宣言
class CCollider;

class CCharacter :public CRectangle,public CTask//親クラス名
{
public:
	enum class EState//状態
	{
		EWAIT,    //待機
		EMOVE,    //移動
		EJUMP,    //ジャンプ
	};
	//デフォルトコンストラクタ
	CCharacter();

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="priority">優先度</param>
	CCharacter(int priority);

	//デストラクタ
	virtual ~CCharacter();

	//mpTextureを返す
	CTexture* GetTexture();

	/// <summary>
	/// 有効フラグを設定
	/// </summary>
	/// <param name="isEnabled"></param>
	void SetEnabled(bool isEnabled);

	//有効フラグを返す
	bool GetEnabled();

	/// <summary>
	/// 処理順番を設定
	/// </summary>
	/// <param name="order">処理順番</param>
	void SetSortOrder(float order);

	//処理順番を取得
	float GetSortOrder();

	/// <summary>
	/// テクスチャの設定
	/// </summary>
	/// <param name="pTexture">テクスチャのポインタ</param>
	/// <param name="left">テクスチャの左座標</param>
	/// <param name="right">テクスチャの右座標</param>
	/// <param name="bottom">テクスチャの下座標</param>
	/// <param name="top">テクスチャの上座標</param>
	void Texture(CTexture* pTexture,int left, int right, int bottom, int top);

	void Render();//描画

	//衝突処理
	virtual void Collision(CCollider* m, CCollider* o) {}

protected:
	EState mState;      //状態

	float mVx, mVy;		//速度
private:
	CTexture* mpTexture;//テクスチャ

	int mLeft, mRight, mBottom, mTop;//左、右、下、上

};

