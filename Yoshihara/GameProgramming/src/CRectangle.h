#pragma once

class CRectangle
{
public:
	CRectangle();
	~CRectangle();

	void Render();
	void Render(float x, float y, float w, float h);
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