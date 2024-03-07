#pragma once

#include "CCharacter.h"
#include "CInput.h"

#define ENEMY_TEXTURE "ザコ＿スライム＿移動.png"

class CPlayer : public CCharacter
{
public:
	CPlayer();

	/// <summary>
	/// プレイヤーを設定
	/// </summary>
	/// <param name="x">X座標</param>
	/// <param name="y">Y座標</param>
	/// <param name="w">幅</param>
	/// <param name="h">高さ</param>
	/// <param name="pt">テクスチャのポインタ</param>
	CPlayer(float x, float y,float w ,float h, CTexture* pt);

	//更新処理
	void Update();

private:
	CInput mInput;
};