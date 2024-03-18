#include "CTaskManager.h"

//デフォルトコンストラクタ
CTaskManager::CTaskManager()
{
	mHead.mpNext = &mTail;
	mTail.mpPrev = &mHead;
	mHeadObj.mpNextObj = &mTailObj;
	mTailObj.mpPrevObj = &mHeadObj;
	mHeadBackground.mpNextBackground = &mTailBackground;
	mTailBackground.mpPrevBackground = &mHeadBackground;
}

//デストラクタ
CTaskManager::~CTaskManager()
{
}

//リストに追加
void CTaskManager::Add(CTask* addTask, bool isSort)
{
	if (!isSort)
	{
		//addTaskの優先度がオブジェクト用ならオブジェクトのリストに追加
		if (addTask->mPriority == (int)CTaskPriority::Object)
		{
			CTask* taskObj = mHeadObj.mpNextObj;
			//addTaskの次をtaskObj
			addTask->mpNextObj = taskObj;
			//addTaskの前をtaskObjの前に
			addTask->mpPrevObj = taskObj->mpPrevObj;
			//addTaskの前の次をaddTaskに
			addTask->mpPrevObj->mpNextObj = addTask;
			//taskObjの前をaddTaskに
			taskObj->mpPrevObj = addTask;
		}
		//addTaskの優先度がオブジェクト用ならオブジェクトのリストに追加
		if (addTask->mPriority == (int)CTaskPriority::Field)
		{
			CTask* taskBackground = mHeadBackground.mpNextBackground;
			//addTaskの次をtaskBackground
			addTask->mpNextBackground = taskBackground;
			//addTaskの前をtaskBackgroundの前に
			addTask->mpPrevBackground = taskBackground->mpPrevBackground;
			//addTaskの前の次をaddTaskに
			addTask->mpPrevBackground->mpNextBackground = addTask;
			//taskBackgroundの前をaddTaskに
			taskBackground->mpPrevBackground = addTask;
		}
	}
	//mHeadの次から検索
	CTask* task = mHead.mpNext;

	//優先度の大きい順に挿入
	//優先度が小さければ次のタスクへ
	//優先度が同じか大きくなったら前に挿入
	while (addTask->mPriority < task->mPriority)
	{
		task = task->mpNext;
	}
	//優先度が同じかつ優先度がオブジェクト用なら処理順番が大きい順に入れる
	while (addTask->mPriority == task->mPriority && addTask->mPriority == (int)CTaskPriority::Object)
	{
		if (addTask->mSortOrder > task->mSortOrder)
		{
			//addTaskの次をtask
			addTask->mpNext = task;
			//addTaskの前をtaskの前に
			addTask->mpPrev = task->mpPrev;
			//addTaskの前の次をaddTaskに
			addTask->mpPrev->mpNext = addTask;
			//taskの前をaddTaskに
			task->mpPrev = addTask;
			return;
		}
		task = task->mpNext;
	}
	//優先度が同じかつ優先度が背景用なら処理順番が大きい順に入れる
	while (addTask->mPriority == task->mPriority && addTask->mPriority == (int)CTaskPriority::Field)
	{
		if (addTask->mSortOrder > task->mSortOrder)
		{
			//addTaskの次をtask
			addTask->mpNext = task;
			//addTaskの前をtaskの前に
			addTask->mpPrev = task->mpPrev;
			//addTaskの前の次をaddTaskに
			addTask->mpPrev->mpNext = addTask;
			//taskの前をaddTaskに
			task->mpPrev = addTask;
			return;
		}
		task = task->mpNext;
	}
	//優先度が大きいなら前に挿入
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
void CTaskManager::Remove(CTask* removeTask, bool isSort)
{
	if (!isSort)
	{
		//優先度がオブジェクト用であれば、オブジェクトのリストからも取り除く
		if (removeTask->mPriority == (int)CTaskPriority::Object)
		{
			//removeTaskの前の次を、removeTaskの次にする
			removeTask->mpPrevObj->mpNextObj = removeTask->mpNextObj;
			//removeTaskの次の前を、removeTaskの前にする
			removeTask->mpNextObj->mpPrevObj = removeTask->mpPrevObj;
		}
		//優先度が背景用であれば、背景のリストからも取り除く
		if (removeTask->mPriority == (int)CTaskPriority::Field)
		{
			//removeTaskの前の次を、removeTaskの次にする
			removeTask->mpPrevBackground->mpNextBackground = removeTask->mpNextBackground;
			//removeTaskの次の前を、removeTaskの前にする
			removeTask->mpNextBackground->mpPrevBackground = removeTask->mpPrevBackground;
		}
	}
	//タスクの前の次を、タスクの次にする
	removeTask->mpPrev->mpNext = removeTask->mpNext;
	//タスクの次の前を、タスクの前にする
	removeTask->mpNext->mpPrev = removeTask->mpPrev;
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

//タスクマネージャのインスタンス
CTaskManager* CTaskManager::mpInstance = nullptr;

//インスタンスの取得
CTaskManager* CTaskManager::GetInstance()
{
	//インスタンスがなければ
	if (mpInstance == nullptr)
	{
		//インスタンスを生成
		mpInstance = new CTaskManager();
	}
	return mpInstance;
}

