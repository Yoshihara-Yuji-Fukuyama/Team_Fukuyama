#include "CShadowManager.h"
#include "CTaskManager.h"
#include "CObjectBase.h"

//コンストラクタ
CShadowManager::CShadowManager()
	:CTask((int)CTaskPriority::Shadow)
	, mpImage(nullptr)
{
	//影の画像を読み込む
	mpImage = CImage::CreateImage("shadow.png");
	mpImage->SetCenter(52.0f, 16.0f);
		
}

//デストラクタ
CShadowManager::~CShadowManager()
{
	//影の画像データを削除
	delete mpImage;
}

//更新
void CShadowManager::Update()
{

}

//描画
void CShadowManager::Render()
{
	//オブジェクトリストを取得
	auto& objects = CTaskManager::GetObjectList();
	for (CTask* task : objects)
	{
		CObjectBase* obj = dynamic_cast<CObjectBase*>(task);
		if (obj == nullptr)continue;

		//各オブジェクトの座標に影の画像を描画
		mpImage->SetPos(obj->GetPos());
		mpImage->Draw();
	}
}