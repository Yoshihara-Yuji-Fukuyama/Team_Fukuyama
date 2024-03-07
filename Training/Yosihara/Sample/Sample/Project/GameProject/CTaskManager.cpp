#include "CTaskManager.h"
#include "CTask.h"
#include "CObjectBase.h"

//タスクのリストを定義
std::list<CTask*>CTaskManager::mTaskList;
//オブジェクトのリストを定義
std::list<CTask*>CTaskManager::mObjectList;

//コンストラクタ
CTaskManager::CTaskManager()
{

}

//デストラクタ
CTaskManager::~CTaskManager()
{

}

//タスクをリストに追加
void CTaskManager::Add(CTask* add, bool isSort)
{
	if (!isSort)
	{
		//追加するタスクの優先度がオブジェクト用であれば
		//オブジェクトリストに追加
		if (add->mPriority == (int)CTaskPriority::Object)
		{
			mObjectList.push_back(add);
		}
	}
	auto itr = mTaskList.begin();
	auto end = mTaskList.end();
	while (itr != end)
	{
		CTask* task = *itr;
		//追加するタスクの優先度＜現在のタスクの優先度ならば、
		//その位置にタスクを追加
		if (add->mPriority < task->mPriority)
		{
			mTaskList.insert(itr, add);
			return;
		}
		//追加するタスクの優先度と現在のタスクの優先度が同じならば
		else if (add->mPriority = task->mPriority)
		{
			//処理順番が小さい順に並べる
			if (add->mSortOrder < task->mSortOrder)
			{
				mTaskList.insert(itr, add);
				return;
			}
		}
		itr++;
	}
	//最後まで追加する場所が見つからなかった場合は、
	//リストの最後尾に追加する
	mTaskList.push_back(add);
}

//タスクをリストから取り除く
void CTaskManager::Remove(CTask* remove, bool isSort)
{
	//ソート時の呼び出しではない
	if (!isSort)
	{
		//優先度がオブジェクト用であれば、オブジェクトリストからも取り除く
		if (remove->mPriority == (int)CTaskPriority::Object)
		{
			mObjectList.remove(remove);
		}
	}
	mTaskList.remove(remove);
}

//タスクを削除
void CTaskManager::Delete(CTask* del)
{
	//削除するタスクがオブジェクトであれば、オブジェクトリストから取り除く
	if (del->mPriority == (int)CTaskPriority::Object)
	{
		mObjectList.remove(del);
	}
	//削除するときは、先にリストから取り除いてから削除する
	mTaskList.remove(del);
	delete del;
}

//リスト内のタスクをすべて削除
void CTaskManager::DeleteAll()
{
	//全て削除するので、オブジェクトリストの中身すべてクリアする
	mObjectList.clear();

	auto itr = mTaskList.begin();
	auto end = mTaskList.end();
	while (itr != end)
	{
		CTask* del = *itr;
		//リストから取り除いてから、タスクを削除
		itr = mTaskList.erase(itr);
		delete del;
	}
}

const std::list<CTask*>& CTaskManager::GetObjectList()
{
	return mObjectList;
}

//リスト内の全タスクの更新処理を呼び出す
void CTaskManager::Update()
{
	//削除フラグが立っているタスクを削除
	auto itr = mTaskList.begin();
	auto end = mTaskList.end();
	while (itr != end)
	{
		CTask* task = *itr;
		if (task->mIsKill)
		{
			itr = mTaskList.erase(itr);
			delete task;
		}
		//削除フラグが立ってなければ、次のタスクへ
		else
		{
			itr++;
		}
	}
	//すべてのタスクを更新
	itr = mTaskList.begin();
	end = mTaskList.end();
	while (itr != end)
	{
		CTask* task = *itr;
		if (task->mIsEnable)
		{
			task->Update();
		}
		itr++;
	}
}
//リスト内の全タスクの描画処理を呼び出す
void CTaskManager::Render()
{
	//オブジェクトリストの中のオブジェクトを
	//奥行の座標で並び変える
	mObjectList.sort
	(
		[](const CTask* taskA, const CTask* taskB)
		{
			const CObjectBase* objA = dynamic_cast<const CObjectBase*>(taskA);
			const CObjectBase* objB = dynamic_cast<const CObjectBase*>(taskB);
			return objA->GetPos().y < objB->GetPos().y;
		}
	);
	//オブジェクトリストの順番に処理順番の番号を設定する
	int SortOrder = 0;
	for (auto& obj : mObjectList)
	{
		obj->SetSortOrder(SortOrder);
		SortOrder++;
	}

	auto itr = mTaskList.begin();
	auto end = mTaskList.end();
	while (itr != end)
	{
		CTask* task = *itr;
		//タスクが有効かつ、表示する設定であれば、
		//描画処理を呼び出す
		if (task->mIsEnable && task->mIsShow)
		{
			task->Render();
		}
		itr++;

	}
}