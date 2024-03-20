#pragma once

class CTaskManager;
class CCollisionManager;

enum class CTaskPriority
{
	Title,    //タイトル
	UI,      //UI
	Object,  //オブジェクト
	Shadow,  //影
	Field,   //背景
	Collider,//当たり判定
};

class CTask
{
	friend CTaskManager;
	friend CCollisionManager;
public:
	//デフォルトコンストラクタ
	CTask()
		:mpNext(nullptr), mpPrev(nullptr), mpNextObj(nullptr), mpPrevObj(nullptr)
		, mPriority(0), mSortOrder(0), mEnabled(true) {}
	//デストラクタ
	virtual ~CTask() {}
	//更新
	virtual void Update() {}
	//描画
	virtual void Render() {}
	//衝突
	virtual void Collision() {}

protected:
	int mPriority;//優先度
	int mSortOrder;//処理順番
	bool mEnabled;//有効フラグ

private:
	CTask* mpNext;//次のポインタ
	CTask* mpPrev;//前のポインタ
	CTask* mpNextObj;//オブジェの次のポインタ
	CTask* mpPrevObj;//オブジェの前のポインタ
	CTask* mpNextBackground;//背景の次のポインタ
	CTask* mpPrevBackground;//背景の前のポインタ
};
