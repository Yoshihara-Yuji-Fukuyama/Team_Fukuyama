#pragma once

class CTaskManager;
class CCollisionManager;

enum class CTaskPriority
{
	SPACE,
	UI,
	Object,
	Field,
	Collider,
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
	CTask* mpNextCollider;//コライダの次のポインタ
	CTask* mpPrevCollider;//コライダの前のポインタ
};
