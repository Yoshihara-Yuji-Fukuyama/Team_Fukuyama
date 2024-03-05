#pragma once

class CRectangle
{
public:
	CRectangle();
	~CRectangle();

	void Render();

	/// <summary>
	/// 四角形の描写
	/// </summary>
	/// <param name="x">X座標</param>
	/// <param name="y">Y座標</param>
	/// <param name="w">幅</param>
	/// <param name="h">高さ</param>
	void Render(float x, float y, float w, float h);

	/// <summary>
	/// 大きさの設定
	/// </summary>
	/// <param name="x">X座標</param>
	/// <param name="y">Y座標</param>
	/// <param name="w">幅</param>
	/// <param name="h">高さ</param>
	void Set(float x, float y, float w, float h);

	float GetX();
	float GetY();
	float GetW();
	float GetH();

private:
	float mX; //X座標
	float mY; //Y座標
	float mW; //幅
	float mH; //高さ

};