#include "CRectangle.h"
#include "CApplication.h"
#define SOUND_BGM "res\\mario.wav" //BGM音声ファイル
#define SOUND_OVER "res\\mdai.wav" //ゲームオーバー音声ファイル

//static変数の定義
CCharacterManager CApplication::mCharacterManager;

CTexture CApplication::mTexture;

CTaskManager CApplication::mTaskManager;

//メソッドの定義
CCharacterManager* CApplication::CharacterManager()
{
	return &mCharacterManager;
}

CTexture* CApplication::Texture()
{
	return &mTexture;
}

CTaskManager* CApplication::TaskManager()
{
	return &mTaskManager;
}

void CApplication::Start()
{
	//アクションゲームプログラム

	//Sound
	mSoundBgm.Load(SOUND_BGM);

	mSoundOver.Load(SOUND_OVER);

	mFont.Load("FontWhite.png", 1, 64);

	mState = EState::ESTART;

	mpGame = new CGame();
}



void CApplication::Update()
{
	//アクションゲームプログラム
	switch (mState)
	{

	case EState::ESTART: //状態がスタート

		mpGame->Start(); //スタート画面表示

		//Enterキーが押されたら
		if (mInput.Key(VK_RETURN))
		{
			//状態をプレイ中にする
			mState = EState::EPLAY;

			//BGMリピート再生
			mSoundBgm.Repeat();
		}

		break;



	case EState::EPLAY: //状態がプレイ
		
		mpGame->Update();

		//ゲームクリアか判定
		if (mpGame->IsClear())
		{
			//状態をゲームクリアにする
			mState = EState::ECLEAR;
		}

		//ゲームオーバーか判定
		if (mpGame->IsOver())
		{
			//状態をゲームオーバーにする
			mState = EState::EOVER;

			//BGMストップ
			mSoundBgm.Stop();

			//ゲームオーバー音再生
			mSoundOver.Play();
		}

		break;



	case EState::ECLEAR: //状態がクリア

		//ゲームクリア処理
		mpGame->Clear();

		//エンターキー入力時
		if (mInput.Key(VK_RETURN))
		{
			//ゲームのインスタンス削除
			delete mpGame;

			//ゲームのインスタンス生成
			mpGame = new CGame();

			//状態をスタートにする
			mState = EState::ESTART;
		}

		break;




	case EState::EOVER: //状態がゲームオーバー

		//ゲームオーバー処理
		mpGame->Over();

		//エンターキー入力時
		if (mInput.Key(VK_RETURN))
		{
			//ゲームのインスタンス削除
			delete mpGame;

			//ゲームのインスタンス生成
			mpGame = new CGame();

			//状態をスタートにする
			mState = EState::ESTART;
		}

		break;
	}
}

