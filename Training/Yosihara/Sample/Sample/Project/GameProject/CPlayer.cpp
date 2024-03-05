#include "CPlayer.h"

//コンストラクタ
CPlayer::CPlayer()
	:mPos(CVector2D(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.75f))
	, mpAnimData(nullptr)
	, mpImage(nullptr)
	, mHp(100)
{

	//プレイヤーのアニメーションデータを生成
	int frame = 6;
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
		"player.png",//画像ファイルのパス
		mpAnimData,//アニメーションのデータ
		384.0f,384.0f//1コマの幅と高さ
	);
	mpImage->ChangeAnimation(0);
	mpImage->SetCenter(192.0f, 328.0f);
}

//デストラクタ
CPlayer::~CPlayer()
{
	//アニメーションのデータの配列を削除
	for (int i = 0; i < 2; i++)
	{
		delete[] mpAnimData[i].pData;
	}
	delete[] mpAnimData;
	//画像データを削除
	delete[] mpImage;
}

//プレイヤーの座標を取得
const CVector2D& CPlayer::GetPos() const
{
	return mPos;
}

//プレイヤーの座標を設定
void CPlayer::SetPos(const CVector2D& pos)
{
	mPos = pos;
}

//更新処理
void CPlayer::Update()
{
	bool isMove = false;
	//左キーを押している間
	if (HOLD(CInput::eLeft))
	{
		//左方向へ移動
		mPos.x -= 5.0f;
		mpImage->ChangeAnimation(1);
		mpImage->SetFlipH(true);
		isMove = true;
	}
	//右キーを押している間
	else if (HOLD(CInput::eRight))
	{
		//右方向へ移動
		mPos.x += 5.0f;
		mpImage->ChangeAnimation(1);
		mpImage->SetFlipH(false);
		isMove = true;
	}
	//上キーを押している間
	if (HOLD(CInput::eUp))
	{
		//上方向へ移動
		mPos.y -= 3.0f;
		mpImage->ChangeAnimation(1);
		isMove = true;

	}
	//下キーを押している間
	else if (HOLD(CInput::eDown))
	{
		//下方向へ移動
		mPos.y += 3.0f;
		mpImage->ChangeAnimation(1);
		isMove = true;
	}
	//押されていない場合
	if(!isMove)
	{
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