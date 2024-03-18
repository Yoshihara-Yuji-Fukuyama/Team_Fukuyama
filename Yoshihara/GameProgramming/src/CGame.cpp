#include "CGame.h"
#include "CApplication.h"
#include "CCamera.h"
#include "main.h"
#include "CCollisionManager.h"
#include <time.h>
#include "CBackground.h"

#define TEXTURE_PLAYER "Player.png"          //�v���C���[�摜

#define TEXTURE_SLIME "Slime.png"            //�X���C���摜
#define TEXTURE_ONI "Oni.png"                //�S�摜

#define TEXTURE_SKY "Sky.png"                //��摜
#define TEXTURE_CLOUD_A "CloudA.png"         //�_A�摜
#define TEXTURE_CLOUD_B "CloudB.png"         //�_B�摜
#define TEXTURE_CLOUD_C "CloudC.png"         //�_C�摜
#define TEXTURE_BUILDING "Building.png"      //�����摜
#define TEXTURE_ROAD "Road.png"              //���摜

#define TEXTURE_HP_BAR "Hp.png"              //HP�摜
#define TEXTURE_FRAME "Frame.png"            //�g�摜

#define BACKGROUND_SET1 960.0f,540.0f,960.0f,540.0f//x,y,w,h�@�w�i1�̏����ʒu
#define BACKGROUND_SET2 2880.0f,540.0f,960.0f,540.0f//x,y,w,h �w�i2�̏����ʒu
#define CHARACTER_SIZE 300.0f,300.0f                //w,h  �L�����N�^�[�̃T�C�Y
#define HP_SIZE_RED 235.0f, 12.0f                   //w,h  HpRed�̃T�C�Y
#define HP_SIZE_YELLOW 184.0f,12.0f                 //w,h HpYellow�̃T�C�Y
#define FACE_SIZE 50.0f,50.0f                     //w,h Face�̃T�C�Y
#define FRAME_SIZE 60.0,60.0f                     //w,h Frame�̃T�C�Y

#define SLIME_HP 100 //�X���C��HP
#define ONI_HP 100 //�SHP

#define ENEMY_MAX 4 //�G�̍ő吔

CGame::CGame()
	:mFrame(0)
{		
	count = 1;//�b���J�E���^

	//�e�N�X�`�������[�h
	CPlayer::GetTexture()->Load(TEXTURE_PLAYER);

	CEnemy::GetTextureSlime()->Load(TEXTURE_SLIME);
	CEnemy::GetTextureOni()->Load(TEXTURE_ONI);

	CBackground::GetTextureSky()->Load(TEXTURE_SKY);
	CBackground::GetTextureCloudA()->Load(TEXTURE_CLOUD_A);
	CBackground::GetTextureCloudB()->Load(TEXTURE_CLOUD_B);
	CBackground::GetTextureCloudC()->Load(TEXTURE_CLOUD_C);
	CBackground::GetTextureBuilding()->Load(TEXTURE_BUILDING);
	CBackground::GetTextureRoad()->Load(TEXTURE_ROAD);

	CUiTexture::GetTextureHpBar()->Load(TEXTURE_HP_BAR);
	CUiTexture::GetTextureFrame()->Load(TEXTURE_FRAME);
	CUiTexture::GetTextureFace()->Load(TEXTURE_PLAYER);

	//�w�i����
	new CBackground(BACKGROUND_SET1, nullptr, nullptr, (int)EFieldSort::Sky);
	new CBackground(BACKGROUND_SET2, nullptr, nullptr, (int)EFieldSort::Sky);
	new CBackground(BACKGROUND_SET1, nullptr, nullptr, (int)EFieldSort::CloudA);
	new CBackground(BACKGROUND_SET1, nullptr, nullptr, (int)EFieldSort::CloudB);
	new CBackground(BACKGROUND_SET1, nullptr, nullptr, (int)EFieldSort::CloudC);
	new CBackground(BACKGROUND_SET1, nullptr, nullptr, (int)EFieldSort::Building);
	new CBackground(BACKGROUND_SET1, nullptr, nullptr, (int)EFieldSort::Road);
	new CBackground(BACKGROUND_SET2, nullptr, nullptr, (int)EFieldSort::Road);

	//Ui����
	new CUiTexture(FRAME_SIZE, CUiTexture::EUiType::Frame);
	new CUiTexture(FACE_SIZE, CUiTexture::EUiType::Face);
	new CUiTexture(HP_SIZE_YELLOW, CUiTexture::EUiType::HpYellow);
	new CUiTexture(HP_SIZE_RED, CUiTexture::EUiType::HpRed);
	
	//�v���C���[����
	CPlayer::GetInstance();
}



void CGame::Update()
{	
	//���Ԃ�0�ɂȂ������~
	if (CUiFont::GetInstance()->GetTime() > 0)
	{
		clock_t end = clock();//�o�ߎ���
		double sec = (double)(end) / CLOCKS_PER_SEC;//�b���ɕϊ�
		if (sec >= count)
		{
			//1�b�}�C�i�X
			CUiFont::GetInstance()-> SetTime();
			count++;
		}
		//�G����
		CreateEnemy();
		//�폜
		CTaskManager::GetInstance()->Delete();
		//�X�V
		CTaskManager::GetInstance()->Update();

	}
		//�Փ˔���
		//CCollisionManager::GetInstance()->Collision();

		//�J������ݒ�
		SetCamera();

		//�`��
		CTaskManager::GetInstance()->Render();

		//�R���C�_�̕\��(�m�F�p)
		//CCollisionManager::GetInstance()->Render();

		CCamera::End();

		//�e�L�X�g�nUI�`��
		CUiFont::GetInstance()->Render();


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

	int posY = rand() % 100 + 150;//150����250�����̒l�������_��

	//frame/CREATE_TIME�̂��܂肪CREATE_TIME�̔����̐��l�̔{���Ȃ琶��
	//�G�̐����ő�l�Ȃ琶�����Ȃ�
	if (frame % CREATE_TIME % (CREATE_TIME / 2) == 0 && CEnemy::GetEnemyCount() < ENEMY_MAX)
	{

			//�L�����^�C�v�������Ȃ�X���C��
			if (charaType % 2 == 0)
			{
				new CEnemy(CPlayer::GetInstance()->GetX() + 1000, posY, CHARACTER_SIZE, SLIME_HP, CEnemy::EEnemyType::Slime);
				//�G�̐����P���Z
				CEnemy::PlusEnemyCount();
			}
			//��Ȃ�S
			else
			{
				new CEnemy(CPlayer::GetInstance()->GetX() + 1000, posY, CHARACTER_SIZE, ONI_HP, CEnemy::EEnemyType::Oni);
				//�G�̐����P���Z
				CEnemy::PlusEnemyCount();
			}
	}
}
