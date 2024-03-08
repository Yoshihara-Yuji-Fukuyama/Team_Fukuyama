#pragma once
#include "CTexture.h"
#include "CRectangle.h"
#include "CTask.h"

class CCharacter :public CRectangle,public CTask//親クラス名
{
public:
	//デフォルトコンストラクタ
	CCharacter();
	/// <summary>
	/// 背景のコンストラクタ
	/// </summary>
	/// <param name="priority">優先度</param>
	CCharacter(int priority);
	//デストラクタ
	~CCharacter();
	//mpTextureを返す
	CTexture* GetTexture();
	//有効フラグを返す
	bool GetEnabled();

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

protected:
	bool mEnabled;//有効フラグ

private:
	CTexture* mpTexture;//テクスチャ

	int mLeft, mRight, mBottom, mTop;//左、右、下、上

};

