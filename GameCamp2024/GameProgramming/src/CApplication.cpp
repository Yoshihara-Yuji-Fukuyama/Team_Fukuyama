#include "CRectangle.h"
#include "CApplication.h"
#define SOUND_BGM "res\\mario.wav" //BGM�����t�@�C��
#define SOUND_OVER "res\\mdai.wav" //�Q�[���I�[�o�[�����t�@�C��

//static�ϐ��̒�`
CCharacterManager CApplication::mCharacterManager;

CTexture CApplication::mTexture;

CTaskManager CApplication::mTaskManager;

//���\�b�h�̒�`
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
	//�A�N�V�����Q�[���v���O����

	//Sound
	mSoundBgm.Load(SOUND_BGM);

	mSoundOver.Load(SOUND_OVER);

	mFont.Load("FontWhite.png", 1, 64);

	mState = EState::ESTART;

	mpGame = new CGame();
}



void CApplication::Update()
{
	//�A�N�V�����Q�[���v���O����
	switch (mState)
	{

	case EState::ESTART: //��Ԃ��X�^�[�g

		mpGame->Start(); //�X�^�[�g��ʕ\��

		//Enter�L�[�������ꂽ��
		if (mInput.Key(VK_RETURN))
		{
			//��Ԃ��v���C���ɂ���
			mState = EState::EPLAY;

			//BGM���s�[�g�Đ�
			mSoundBgm.Repeat();
		}

		break;



	case EState::EPLAY: //��Ԃ��v���C
		
		mpGame->Update();

		//�Q�[���N���A������
		if (mpGame->IsClear())
		{
			//��Ԃ��Q�[���N���A�ɂ���
			mState = EState::ECLEAR;
		}

		//�Q�[���I�[�o�[������
		if (mpGame->IsOver())
		{
			//��Ԃ��Q�[���I�[�o�[�ɂ���
			mState = EState::EOVER;

			//BGM�X�g�b�v
			mSoundBgm.Stop();

			//�Q�[���I�[�o�[���Đ�
			mSoundOver.Play();
		}

		break;



	case EState::ECLEAR: //��Ԃ��N���A

		//�Q�[���N���A����
		mpGame->Clear();

		//�G���^�[�L�[���͎�
		if (mInput.Key(VK_RETURN))
		{
			//�Q�[���̃C���X�^���X�폜
			delete mpGame;

			//�Q�[���̃C���X�^���X����
			mpGame = new CGame();

			//��Ԃ��X�^�[�g�ɂ���
			mState = EState::ESTART;
		}

		break;




	case EState::EOVER: //��Ԃ��Q�[���I�[�o�[

		//�Q�[���I�[�o�[����
		mpGame->Over();

		//�G���^�[�L�[���͎�
		if (mInput.Key(VK_RETURN))
		{
			//�Q�[���̃C���X�^���X�폜
			delete mpGame;

			//�Q�[���̃C���X�^���X����
			mpGame = new CGame();

			//��Ԃ��X�^�[�g�ɂ���
			mState = EState::ESTART;
		}

		break;
	}
}

