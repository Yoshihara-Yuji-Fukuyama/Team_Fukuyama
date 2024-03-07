#pragma once
#include <list>

class CTask;

//タスクを管理するクラス
class CTaskManager
{
public:
	/// <summary>
	/// タスクをリストに追加
	/// </summary>
	/// <param name="add">追加するタスク</param>
	/// <param name="isSort">ソート時の呼び出しかどうか</param>
	static void Add(CTask* add, bool isSort = false);
	/// <summary>
	/// タスクをリストから取り除く
	/// </summary>
	/// <param name="remove">取り除くタスクのポインタ―</param>
	/// <param name="isSort">ソート時の呼び出しかどうか</param>
	static void Remove(CTask* remove, bool isSort = false);

	/// <summary>
	/// タスクを削除
	/// </summary>
	/// <param name="del">削除するタスクのポインター</param>
	static void Delete(CTask* del);
	//リスト内のタスクをすべて削除
	static void DeleteAll();

	//リスト内の全タスクの更新処理を呼び出す
	static void Update();
	//リスト内の全タスクの描画処理を呼び出す
	static void Render();
private:
	//コンストラクタ
	CTaskManager();
	//デストラクタ
	~CTaskManager();

	//現在生成されているタスクのリスト
	static std::list<CTask*> mTaskList;
	//現在生成されているオブジェクトのリスト
	static std::list<CTask*> mObjectList;
};