#pragma once

#include "CTask.h"
#include "CCharacter.h"


class CTaskManager
{
public:

	/// <summary>
    /// タスクをリストに追加
    /// </summary>
    /// <param name="add">追加するタスク</param>
    /// <param name="isSort">ソート時の呼び出しかどうか</param>
	void Add(CTask* addTask, bool isSort = false);
	/// <summary>
	/// タスクをリストから取り除く
	/// </summary>
	/// <param name="remove">取り除くタスクのポインタ―</param>
	/// <param name="isSort">ソート時の呼び出しかどうか</param>
	void Remove(CTask* removeTask, bool isSort = false);

	//インスタンスの取得
	static CTaskManager* GetInstance();
	//デストラクタ
	virtual ~CTaskManager();
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
	CTask mHeadObj;//オブジェの先頭タスク
	CTask mTailObj;//最終タスク

	//デフォルトコンストラクタ
	CTaskManager();
private:
	//タスクマネージャーのインスタンス
	static CTaskManager* mpInstance;
};
