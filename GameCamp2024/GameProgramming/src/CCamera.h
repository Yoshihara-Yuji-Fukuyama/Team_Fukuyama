#pragma once

//画面に表示する範囲を設定
class CCamera
{
public:
	/// <summary>
	/// 表示エリアの設定
	/// </summary>
	/// <param name="Left">左</param>
	/// <param name="Right">右</param>
	/// <param name="bottom">下</param>
	/// <param name="top">上</param>
	static void SetCamera(double left, double right
		, double bottom, double top);

	static void End();

};