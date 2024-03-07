#include "CSlime.h"

//コンストラクタ
CSlime::CSlime(int type, const CVector2D& pos)
	: CCharacterBase(pos,50)
	, mpAnimData(nullptr)
	, mpImage(nullptr)
	, mType(type)
{

	//アニメーションデータを生成
	int frame = 4;
	mpAnimData = new TexAnimData[1]
	{
		{
			new TexAnim[4]
			{
				{ 0, frame}, { 1, frame},
		        { 2, frame}, { 3, frame},
			},
			4
		},
	};
	//画像を読み込み
	std::string ImagePath;
	if (mType == 0) ImagePath = "slime_a.png";
	else if (mType == 1) ImagePath = "slime_b.png";
	else if (mType == 2)ImagePath = "slime_c.png";
	mpImage = CImage::CreateImage
	(
		ImagePath.c_str(),//画像ファイルのパス
		mpAnimData,//アニメーションのデータ
		256.0f, 256.0f//1コマの幅と高さ
	);
	mpImage->ChangeAnimation(0);
	mpImage->SetCenter(128.0f, 184.0f);
	mpImage->SetFlipH(true);
}

//デストラクタ
CSlime::~CSlime()
{
	//アニメーションのデータの配列を削除
	for (int i = 0; i < 1; i++)
	{
		delete[] mpAnimData[i].pData;
	}
	delete[] mpAnimData;
	//画像データを削除
	delete[] mpImage;
}


//更新処理
void CSlime::Update()
{
	//イメージに座標を設定して、アニメーションを更新
	mpImage->SetPos(mPos);
	mpImage->UpdateAnimation();
}

//描画処理
void CSlime::Render()
{
	mpImage->Draw();
}