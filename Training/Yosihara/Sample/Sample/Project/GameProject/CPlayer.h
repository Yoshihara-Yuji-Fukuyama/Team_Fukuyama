#pragma once

class CPlayer
{
//アクセス修飾子
//自分以外の外部からアクセスし放題
public:
	//コンストラクタ
	CPlayer();
	//デストラクタ
	~CPlayer();

	/// <summary>
	/// プレイヤーの座標を取得
	/// </summary>
	/// <returns>プレイヤーの座標</returns>
	const CVector2D& GetPos() const;

	/// <summary>
	/// プレイヤーの座標を設定
	/// </summary>
	/// <param name="pos">設定する座標</param>
	void SetPos(const CVector2D& pos);

	//更新処理
	void Update();
	//描画処理
	void Render();

//自分自身のクラスしかアクセスできない
//メンバ変数は基本private
private:
	CVector2D mPos;//プレイヤーの座標
	TexAnimData* mpAnimData;//アニメーションのデータ
	CImage* mpImage;//プレイヤーの画像
	int mHp;//プレイヤーのHP

};
