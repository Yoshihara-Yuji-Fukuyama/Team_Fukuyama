#include "CTask.h"
#include "CTaskManager.h"

//コンストラクタ
CTask::CTask(int priority)
	:mPriority(priority)
	, mSortOrder(0)
	, mIsEnable(true)
	, mIsShow(true)
	, mIsKill(false)
{
	//タスクの生成と同時にCCTaskManagerのリストに自信を追加
	CTaskManager::Add(this);
}

//デストラクタ
CTask::~CTask()
{
	//タスクの削除と同時にCTaskManagerのリストから自信を取り除く
	CTaskManager::Remove(this);
}

//優先度を設定
void CTask::SetPriority(int priority)
{
	mPriority = priority;
	//1回タスクのリストから自信を取り除き、
	//その後もう1度タスクのリストに追加する関数を呼びだすことで
	//新しい優先度の場所にタスクを変更する
	CTaskManager::Remove(this,true);
	CTaskManager::Add(this,true);
}

//優先度を取得
int CTask::GetPriority() const
{
	return mPriority;
}

//処理順番を設定
void CTask::SetSortOrder(int order)
{
	//処理順番を変更後にリスト内の並び替えも行う
	mSortOrder = order;
	CTaskManager::Remove(this, true);
	CTaskManager::Add(this, true);
}

//処理順番を取得
int CTask::GetSortOrder() const
{
	return mSortOrder;
}

//有効かどうかを設定
void CTask::SetEnable(bool enable)
{
	mIsEnable = enable;
}

//有効かどうか取得
bool CTask::IsEnable() const
{
	return mIsEnable;
}

//表示するかどうかを設定
void CTask::SetShow(bool show)
{
	mIsShow = show;
}

//表示するかどうかを取得
bool CTask::IsShow() const
{
	return mIsShow;
}

//タスクを削除
void CTask::Kill()
{
	mIsKill = true;
}

//タスクの削除フラグが立っているか
bool CTask::IsKill() const
{
	return mIsKill;
}

void CTask::Update()
{

}

void CTask::Render()
{

}
