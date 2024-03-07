#include "CPlayer.h"

//基底クラス・・・
//派生クラス・・・

//コンストラクタ
CPlayer::CPlayer()
	:CharaBase(CVector2D(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.75f))
	,mpAnimData(nullptr)
	,mpImage(nullptr)
{
	mHp = 200;

	//プレイヤーのアニメーションデータを生成
	int frame = 6;
	//配列の中身を設定
	mpAnimData = new TexAnimData[2]
	{
		//待機アニメーション
		{
			new TexAnim[6]
			{
				{0,frame},{1,frame},{2,frame},
				{3,frame},{4,frame},{5,frame},
			},
			6
		},
		//移動アニメーション
		{
			new TexAnim[6]
			{
				{6,frame},{7,frame},{8,frame},
				{9,frame},{10,frame},{11,frame},
			},
			6
		},
	};
	//プレイヤーの画像を読み込み
	mpImage = CImage::CreateImage
	(
		"player.png",	//画像ファイルのパス
		mpAnimData,		//アニメーションのデータ
		384.0f, 384.0f	//1コマの幅と高さ
	);
	mpImage->ChangeAnimation(0);
	mpImage->SetCenter(192.0f, 328.0f);
}

//デストラクタ
CPlayer::~CPlayer()
{
	//アニメーションの配列を削除
	for (int i= 0; i < 2; i++)
	{
		delete[] mpAnimData[i].pData;
	}
	delete[] mpAnimData;

	//画像データを削除
	delete mpImage;
}

//死亡したときの処理
void CPlayer::Death()
{
	//基底クラスの死亡処理も呼び出す
	CharaBase::Death();

	//死亡アニメーションを再生して、
	//死亡アニメーションが終わったら、
	//ゲームオーバー画面を表示
}

//更新処理
void CPlayer::Update()
{
	bool isMove = false;
	//左キーを押している間
	if (HOLD(CInput::eLeft))
	{
		//左方向へ移動
		mPos.x -= 8.0f;
		mpImage->ChangeAnimation(1);
		mpImage->SetFlipH(true);
		isMove = true;
	}
	//右キーを押している間
	else if (HOLD(CInput::eRight))
	{
		//右方向へ移動
		mPos.x += 8.0f;
		mpImage->ChangeAnimation(1);
		mpImage->SetFlipH(false);
		isMove = true;
	}
	if (HOLD(CInput::eUp))
	{
		mPos.y -= 3.0f;
		mpImage->ChangeAnimation(1);
		isMove = true;
	}

	else if (HOLD(CInput::eDown))
	{
		mPos.y += 3.0f;
		mpImage->ChangeAnimation(1);
		isMove = true;
	}
	//左右キーどちらも押されていない場合
	if(!isMove)
	{
		//待機アニメーションを再生
		mpImage->ChangeAnimation(0);
	}

	//イメージに座標を設定して、アニメーションを更新
	mpImage->SetPos(mPos);
	mpImage->UpdateAnimation();
}

//描画処理
void CPlayer::Render()
{
	mpImage->Draw();
}