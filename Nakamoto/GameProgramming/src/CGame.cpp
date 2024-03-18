#include "CGame.h"
#include "CApplication.h"
#include "CCamera.h"
#include "main.h"

#include "CCollisionManager.h"

#define TEXTURE_PLAYER "Player.png"          //�v���C���[�摜
#define TEXTURE_BACKGROUND "Background.png"  //�w�i�摜
#define TEXTURE_SLIME "Slime.png"            //�X���C���摜
#define TEXTURE_ONI "Oni.png"                //�S�摜
#define TEXTURE_HP_BAR "Hp.png"              //HP�摜
#define TEXTURE_FRAME "Frame.png"            //�g�摜

#define BACKGROUND_SET1 960.0f,540.0f,960.0f,540.0f//x,y,w,h�@�w�i1�̏����ʒu
#define BACKGROUND_SET2 2880.0f,540.0f,960.0f,540.0f//x,y,w,h �w�i2�̏����ʒu
#define CHARACTER_SIZE 300.0f,300.0f                //w,h  �L�����N�^�[�̃T�C�Y
#define HP_SIZE_RED 380.0f, 20.0f                   //w,h  HpRed�̃T�C�Y
#define HP_SIZE_YELLOW 292.0f,20.0f                 //w,h HpYellow�̃T�C�Y
#define FACE_SIZE 100.0f,100.0f                     //w,h Face�̃T�C�Y
#define FRAME_SIZE 120.0,120.0f                     //w,h Frame�̃T�C�Y

#define SLIME_HP 100 //�X���C��HP
#define ONI_HP 100 //�SHP

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
	new CUiTexture(FRAME_SIZE, CUiTexture::EUiType::Frame);
	new CUiTexture(FACE_SIZE, CUiTexture::EUiType::Face);
	new CUiTexture(HP_SIZE_YELLOW, CUiTexture::EUiType::HpYellow);
	new CUiTexture(HP_SIZE_RED, CUiTexture::EUiType::HpRed);

	//�v���C���[����
	CPlayer::GetInstance();

	new CEnemy(CPlayer::GetInstance()->GetX() + 700, 300, CHARACTER_SIZE, SLIME_HP,CEnemy::EEnemyType::Slime);

	new CEnemy(CPlayer::GetInstance()->GetX() + 1000, 300, CHARACTER_SIZE, ONI_HP,CEnemy::EEnemyType::Oni);
}

void CGame::Update()
{	
	//�G����
	//CreateEnemy();

	//�폜
	CTaskManager::GetInstance()->Delete();
	//�X�V
	CTaskManager::GetInstance()->Update();
	//�Փ˔���
	CCollisionManager::GetInstance()->Collision();
	//�J������ݒ�
	SetCamera();
	//�`��
	CTaskManager::GetInstance()->Render();

	//�R���C�_�̕\��(�m�F�p)
	CCollisionManager::GetInstance()->Render();

	CCamera::End();

	//mUiFont.Render();
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
				new CEnemy(CPlayer::GetInstance()->GetX() + 1000, posY, CHARACTER_SIZE, SLIME_HP,
					CEnemy::EEnemyType::Slime);
				
			}
			//��Ȃ�S
			else
			{
				new CEnemy(CPlayer::GetInstance()->GetX() + 1000, posY, CHARACTER_SIZE, ONI_HP, 
					CEnemy::EEnemyType::Oni);
			}
		}
		//��Ȃ����ɐ���
		else
		{
			//�L�����^�C�v�������Ȃ�X���C��
			if (charaType % 2 == 0)
			{
				new CEnemy(CPlayer::GetInstance()->GetX() - 1000, posY, CHARACTER_SIZE, SLIME_HP,
					CEnemy::EEnemyType::Slime);
			}
			//��Ȃ�S
			else
			{
				new CEnemy(CPlayer::GetInstance()->GetX() - 1000, posY, CHARACTER_SIZE, ONI_HP, 
					CEnemy::EEnemyType::Oni);
			}
		}

	}
}
