#include "CGame.h"
#include "CApplication.h"
#include "CCamera.h"
#include "main.h"

#define TEXTURE_PLAYER "Player.png"          //�v���C���[�摜
#define TEXTURE_BACKGROUND "Background.png"  //�w�i�摜
#define TEXTURE_SLIME "Slime.png"            //�X���C���摜
#define TEXTURE_ONI "Oni.png"                //�S�摜
#define TEXTURE_HP_BAR "Hp.png"              //HP�摜
#define TEXTURE_FRAME "Frame.png"            //�g�摜

#define BACKGROUND_SET1 960.0f,540.0f,960.0f,540.0f//x,y,w,h�@�w�i1�̏����ʒu
#define BACKGROUND_SET2 2880.0f,540.0f,960.0f,540.0f//x,y,w,h �w�i2�̏����ʒu
#define CHARACTER_SIZE 300.0f,300.0f                //w,h  �L�����N�^�[�̃T�C�Y

CGame::CGame()
	:mFrame(0)
{		
	//�e�N�X�`�������[�h
	CPlayer::GetTexture()->Load(TEXTURE_PLAYER);

	CEnemy::GetTextureSlime()->Load(TEXTURE_SLIME);
	CEnemy::GetTextureOni()->Load(TEXTURE_ONI);

	CBackground::GetTexture()->Load(TEXTURE_BACKGROUND);

	CUiTexture::GetTextureHpBar()->Load(TEXTURE_HP_BAR);
	CUiTexture::GetTextureFrame()->Load(TEXTURE_FRAME);
	CUiTexture::GetTextureFace()->Load(TEXTURE_PLAYER);

	//�w�i����
	new CBackground(BACKGROUND_SET1, nullptr, nullptr);
	new CBackground(BACKGROUND_SET2, nullptr, nullptr);

	//Ui����
	new CUiTexture(200.0f, 1000.0f, 200.0f, 200.0f, CUiTexture::EUiType::HpRed);
	//�v���C���[����
	CPlayer::GetInstance();
}



void CGame::Update()
{	
	
	//�G����
	CreateEnemy();
	//�폜
	CTaskManager::GetInstance()->Delete();
	//�X�V
	CTaskManager::GetInstance()->Update();
	//�J������ݒ�
	SetCamera();
	//�`��
	CTaskManager::GetInstance()->Render();
	CCamera::End();

	mUiFont.Render();
}



void CGame::Start()
{

}



CGame::~CGame()
{
	//���ׂč폜
	CTaskManager::GetInstance()->AllDelete();
}

//�J������ݒ�
void CGame::SetCamera()
{
	float x = CPlayer::GetInstance()->GetX();

	CCamera::SetCamera(x - (float)WINDOW_WIDTH / 2
		, x + (float)WINDOW_WIDTH / 2
		, 0
		, WINDOW_HEIGHT);
}

//�G�l�~�[����
void CGame::CreateEnemy()
{
	const int CREATE_TIME = 500;//�����Ԋu�v�Z�p
	int frame = mFrame++;//�t���[���v�Z

	int charaType = rand();//��������������_��

	int posX = rand();//��������������_��
	int posY = rand() % 250;//250�����̒l�������_��

	//frame/CREATE_TIME�̂��܂肪CREATE_TIME�̔����̐��l�̔{���Ȃ琶��
	if (frame % CREATE_TIME % (CREATE_TIME / 2) == 0)
	{
		//�����Ȃ�O���ɐ���
		if (posX % 2 == 0)
		{
			//�L�����^�C�v�������Ȃ�X���C��
			if (charaType % 2 == 0)
			{
				new CEnemy(CPlayer::GetInstance()->GetX() + 1000, posY, CHARACTER_SIZE, CEnemy::EEnemyType::Slime);
			}
			//��Ȃ�S
			else
			{
				new CEnemy(CPlayer::GetInstance()->GetX() + 1000, posY, CHARACTER_SIZE, CEnemy::EEnemyType::Oni);
			}
		}
		//��Ȃ����ɐ���
		else
		{
			//�L�����^�C�v�������Ȃ�X���C��
			if (charaType % 2 == 0)
			{
				new CEnemy(CPlayer::GetInstance()->GetX() - 1000, posY, CHARACTER_SIZE, CEnemy::EEnemyType::Slime);
			}
			//��Ȃ�S
			else
			{
				new CEnemy(CPlayer::GetInstance()->GetX() - 1000, posY, CHARACTER_SIZE, CEnemy::EEnemyType::Oni);
			}
		}

	}
}
