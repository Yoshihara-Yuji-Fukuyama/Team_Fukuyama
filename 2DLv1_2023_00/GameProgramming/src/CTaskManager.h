#ifndef CTaskManager_H
#define CTaskManager_H
//タスククラスのインクルード
#include "CTask.h"
#include "CCharacter.h"

/*
タスクマネージャ
タスクリストの管理
*/
class CTaskManager {
public:
	//デストラクタ
	virtual ~CTaskManager();
	//リストに追加
	//Add(タスクのポインタ)
	void Add(CTask* addTask);
	//リストから削除
	//Remove(タスクのポインタ)
	void Remove(CTask* task);
	//タスクの削除
	void Delete();
	//タスクの全削除
	void AllDelete();
	//衝突処理1
	void Collision();
	//衝突処理3
	//Collision(衝突元のポインタ)
	void Collision(CCharacter* character);
	//更新
	void Update();
	//描画
	void Render();
	//デフォルトコンストラクタ
	CTaskManager();
protected:
	CTask mHead;//先頭タスク
	CTask mTail;//最終タスク
};
#endif