#pragma once

#include "CTask.h"
#include "CCharacter.h"

class CTaskManager
{
public:
	//インスタンスの取得
	static CTaskManager* GetInstance();
	//デストラクタ
	virtual ~CTaskManager();
	//リストに追加
	void Add(CTask* addTask);
	//リストから削除
	void Remove(CTask* addTask);
	//タスクの削除
	void Delete();
	//タスクの全削除
	void AllDelete();
	//更新
	void Update();
	//描画
	void Render();
protected:
	CTask mHead;//先頭タスク
	CTask mTail;//最終タスク
	//デフォルトコンストラクタ
	CTaskManager();
private:
	//タスクマネージャーのインスタンス
	static CTaskManager* mpInstance;
};
