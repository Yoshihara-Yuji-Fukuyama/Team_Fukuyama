#pragma once

//タスククラス
class CTask
{
public:
	//コンストラクタ
	CTask();
	//デストラクタ
	virtual ~CTask();

	/// <summary>
	/// 優先度を設定
	/// </summary>
	/// <param name="priority">設定する優先度</param>
	void SetPriority(int priority);
	/// <summary>
	/// 優先度を取得
	/// </summary>
	/// <returns>優先度</returns>
	int GetPriority() const;

	/// <summary>
	/// 有効かどうかを設定
	/// </summary>
	/// <param name="enable">trueならば有効</param>
	void SetEneble(bool enable);
	/// <summary>
	/// 有効かどうか取得
	/// </summary>
	/// <returns>trueならば有効</returns>
	bool IsEnable() const;

	/// <summary>
	/// 表示するかどうかを設定
	/// </summary>
	/// <param name="show">trueならば表示</param>
	void SetShow(bool show);
	/// <summary>
	/// 表示するかどうかを取得
	/// </summary>
	/// <returns>trueならば表示</returns>
	bool IsShow() const;
	
	//タスクを削除
	void Kill();
	//タスクの削除フラグが立っているか
	bool IsKill() const;

	//更新
	void Update();
	//描画
	void Render();

private:
	int mPriority;//タスクの優先度
	bool mIsEnable;//タスクが有効かどうか
	bool mIsShow;//タスクを描画するかどうか
	bool mIsKill;//タスクの削除フラグ
};
