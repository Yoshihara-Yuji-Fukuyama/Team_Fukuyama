#pragma once
#include "CTaskManager.h"

class CCollisionManager :public CTaskManager
{
public:
	//衝突処理
	void Collision();

	//インスタンスの取得
	static CCollisionManager* GetInstance();
private:
	//マネージャのインスタンス
	static CCollisionManager* mpInstance;
};