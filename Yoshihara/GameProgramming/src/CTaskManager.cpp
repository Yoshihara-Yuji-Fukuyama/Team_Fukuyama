#include "CTaskManager.h"

//デフォルトコンストラクタ
CTaskManager::CTaskManager()
{
	mHead.mpNext = &mTail;
	mTail.mpPrev = &mHead;
}

//デストラクタ
CTaskManager::~CTaskManager() {}

//リストに追加
void CTaskManager::Add(CTask* addTask)
{
	//mTailの前に追加
	CTask* task = &mTail;
	//addTaskの次をtask
	addTask->mpNext = task;
	//addTaskの前をtaskの前に
	addTask->mpPrev = task->mpPrev;
	//addTaskの前の次をaddTaskに
	addTask->mpPrev->mpNext = addTask;
	//taskの前をaddTaskに
	task->mpPrev = addTask;
}

//リストから削除
void CTaskManager::Remove(CTask* task)
{
	//タスクの前の次を、タスクの次にする
	task->mpPrev->mpNext = task->mpNext;
	//タスクの次の前を、タスクの前にする
	task->mpNext->mpPrev = task->mpPrev;
}

//タスクの削除
void CTaskManager::Delete()
{
	//先頭から最後まで繰り返し
	CTask* task = mHead.mpNext;
	while (task->mpNext)
	{
		CTask* del = task;
		//次へ
		task = task->mpNext;
		//mEnabledがfalseなら削除
		if (del->mEnabled == false)
		{
			delete del;
		}
	}
}

//タスクの全削除
void CTaskManager::AllDelete()
{
	//先頭から最後まで繰り返し
	CTask* task = mHead.mpNext;
	while (task->mpNext)
	{
		CTask* del = task;
		//次へ
		task = task->mpNext;
		//削除
		delete del;
	}
}

//更新
void CTaskManager::Update()
{
	//先頭から最後まで繰り返し
	CTask* task = mHead.mpNext;
	while (task->mpNext)
	{
		//更新処理を呼ぶ
		task->Update();
		//次へ
		task = task->mpNext;
	}
}

//描画
void CTaskManager::Render()
{
	//先頭から最後まで繰り返し
	CTask* task = mHead.mpNext;
	while (task->mpNext)
	{
		//描画処理を呼ぶ
		task->Render();
		//次へ
		task = task->mpNext;
	}
}