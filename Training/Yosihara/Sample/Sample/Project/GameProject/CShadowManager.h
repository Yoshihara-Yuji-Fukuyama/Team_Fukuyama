#pragma once
#include "CTask.h"

//すべてのオブジェクトの影を描画する
class CShadowManager :public CTask
{
public:
	//コンストラクタ
	CShadowManager();
	//デストラクタ
	~CShadowManager();

	//更新
	void Update() override;
	//描画
	void Render() override;
private:
	CImage* mpImage;//影の画像データ
};