#pragma once
#include "CCharacter.h"
/*
ポイントクラス
色々なポイントを作成します
*/

class CPoint :public CCharacter
{
public:
	//CPoint(X座標,Y座標,幅,高さ,タグ)
	CPoint(float x, float y, float w, float h, ETag t);

	void Update() {}  //何もしない

	void Render() {}  //描画しない
};