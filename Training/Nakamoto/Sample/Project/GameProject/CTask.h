#pragma once

class CTaskManager;

//タスクの優先度
enum class CTaskPrio
{
	Field,		//フィールド
	Object,		//ゲーム中のオブジェクト

	UI,			//画面に表示するHUDなどのUI
};

//タスククラス
class CTask
{
	friend CTaskManager;

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="prio">優先度</param>
	CTask(int prio);
	//デストラクタ
	virtual ~CTask();

	/// <summary>
	/// 優先度を取得
	/// </summary>
	/// <param name="prio">設定する優先度</param>
	/// <returns></returns>
	void SetPriority(int prio);
	/// <summary>
	/// 優先度の取得
	/// </summary>
	/// <returns></returns>
	int GetPriority() const;

	/// <summary>
	/// 優先度を設定
	/// </summary>
	/// <param name="order">設定する優先度</param>
	void SetSortOrder(int order);
	/// <summary>
	/// 処理順番を取得
	/// </summary>
	/// <returns></returns>
	int GetSortOrder() const;

	/// <summary>
	/// 有効かどうかを設定
	/// </summary>
	/// <param name="enable">trueならば有効</param>
	void SetEnable(bool enable);
	/// <summary>
	/// 有効かどうかを取得
	/// </summary>
	/// <returns>trueならば有効</returns>
	bool IsEnable() const;

	/// <summary>
	/// 表示するかどうかを設定
	/// </summary>
	/// <param name="show">trueならば表示する</param>
	void SetShow(bool show);
	/// <summary>
	/// 表示するかどうかを取得
	/// </summary>
	/// <returns>trueならば表示する</returns>
	bool IsShow() const;

	//タスクを削除
	void Kill();
	//タスクの削除フラグが立っているか
	bool IsKill();

	//更新
	virtual void Update();
	//描画
	virtual void Render();
private:
	int mPrio;		//タスクの優先度
	int mSortOrder; //同じ優先度内の処理順番
	bool mIsEnable;	//タスクが有効かどうか
	bool mIsShow;	//タスクを描画するかどうか
	bool mIsKill;	//タスクの削除フラグ
};