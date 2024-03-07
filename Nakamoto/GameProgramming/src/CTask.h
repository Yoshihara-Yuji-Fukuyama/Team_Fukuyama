#pragma once

class CTaskManager;

class CTask
{
	friend CTaskManager;
public:
	//デフォルトコンストラクタ
	CTask()
		:mpNext(nullptr), mpPrev(nullptr), mPriority(0), mEnabled(true) {}
	//デストラクタ
	virtual void Update() {}
	//描画
	virtual void Render() {}
	//衝突
	virtual void Collision() {}
protected:
	int mPriority;//優先度
	bool mEnabled;//有効フラグ
private:
	CTask* mpNext;//次のポインタ
	CTask* mpPrev;//前のポインタ
};