#include "CTask.h"

//コンストラクタ
CTask::CTask()
{

}

//デストラクタ
CTask::~CTask()
{

}

//優先度を設定
void CTask::SetPriority(int priority)
{

}

//優先度を取得
int CTask::GetPriority() const
{

}

//有効かどうかを設定
void CTask::SetEnable(bool enable)
{

}

//有効かどうか取得
bool CTask::IsEnable() const
{

}

//表示するかどうかを設定
void CTask::SetShow(bool show)
{
}

//表示するかどうかを取得
bool CTask::IsShow() const
{
	return false;
}

//タスクを削除
void CTask::Kill()
{
}

//タスクの削除フラグが立っているか
bool CTask::IsKill() const
{
	return false;
}
