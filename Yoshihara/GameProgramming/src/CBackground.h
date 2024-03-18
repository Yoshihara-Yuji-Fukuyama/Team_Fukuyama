#pragma once
#include "CCharacter.h"
#include "CPlayer.h"
#include"CInput.h"

enum class EFieldSort
{
	Road,
	Building,
	CloudC,
	CloudB,
	CloudA,
	Sky,
};

class CBackground :public CCharacter
{
public:

	void Update();

	//背景のデフォルトコンストラクタ
	CBackground();

	/// <summary>
	/// 背景のコンストラクタ
	/// </summary>
	/// <param name="x">X座標</param>
	/// <param name="y">Y座標</param>
	/// <param name="w">幅</param>
	/// <param name="h">高さ</param>
	/// <param name="next">次の次の背景のポインタ</param>
	/// <param name="prev">前の前の背景のポインタ</param>
	CBackground(float x, float y, float w, float h,
		CBackground* next2, CBackground* prev2, int sortOrder, float distanceX = 0);

	/// <summary>
	/// 背景生成
	/// </summary>
	/// <param name="background">背景のポインタ</param>
	/// <param name="player">プレイヤーのポインタ</param>
	void CreateBackground(CBackground* background, CPlayer* player);
	/// <summary>
	/// 背景削除
	/// </summary>
	/// <param name="background">背景のポインタ</param>
	/// <param name="player">プレイヤーのポインタ</param>
	void DeleteBackground(CBackground* background, CPlayer* player);

	//staticメソッドの宣言
	static CTexture* GetTextureSky();
	static CTexture* GetTextureCloudA();
	static CTexture* GetTextureCloudB();
	static CTexture* GetTextureCloudC();
	static CTexture* GetTextureBuilding();
	static CTexture* GetTextureRoad();

private:
	float X;//背景のX座標計算用
	CInput mInput;
	CBackground* NextBackground;//次の次の背景のポインタ
	CBackground* PrevBackground;//前の前の背景のポインタ

	//static変数の宣言
	static CTexture mTextureSky;
	static CTexture mTextureCloudA;
	static CTexture mTextureCloudB;
	static CTexture mTextureCloudC;
	static CTexture mTextureBuilding;
	static CTexture mTextureRoad;
};
