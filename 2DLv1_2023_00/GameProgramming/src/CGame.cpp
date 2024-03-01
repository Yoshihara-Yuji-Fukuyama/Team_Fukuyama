#include "CGame.h"
#include "CApplication.h"
#include "CBlock.h"
#include "CPlayer2.h"
#include "CEnemy2.h"
#include "CPoint.h"
#include "CCamera.h"
#include "main.h"


CGame::CGame()
	:mpUi(nullptr)
	, mTime(0)
{
	mpEnemy2->Enemy0(); //�G�̐����[���ɐݒ�

	mpUi = new CUi(); //UI�N���X�̃C���X�^���X�̐���

	//�e�N�X�`���̓���
	CApplication::Texture()->Load(TEXTURE);

	//�萔�̒�`
	const int ROWS = 15; //�s��

	const int COLS = 20; //��

	//2�����z��̃}�b�v
	int map[ROWS][COLS] =
	{
		{1,0,0,1,1,1,1,0,0,0,0,0,0,1,1,1,0,0,0,0},
		{0,0,0,0,2,1,0,0,0,0,0,0,0,1,0,0,0,0,1,1},
		{0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0},
		{0,1,1,1,0,0,0,1,1,1,1,1,0,0,0,0,1,1,1,0},
		{0,0,0,0,0,0,4,0,0,3,0,0,4,0,1,0,0,0,0,0},
		{1,0,0,1,1,1,1,0,0,0,0,0,0,1,1,1,0,0,0,0},
		{0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,1,1},
		{0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0},
		{0,1,1,1,0,0,0,1,1,1,1,1,0,0,0,0,1,1,1,0},
		{0,0,0,0,0,0,4,0,0,3,0,0,4,0,1,0,0,0,0,0},
		{1,0,0,1,1,1,1,0,0,0,0,0,0,1,1,1,0,0,0,0},
		{0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,1,1},
		{0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0},
		{0,1,1,1,0,0,0,1,1,1,1,1,0,0,0,0,1,1,1,0},
		{0,0,0,0,0,0,4,0,0,3,0,0,4,0,1,0,0,0,0,0},
	};

	//�}�b�v�̍쐬
	//�s�����J��Ԃ�
	for (int row = 0; row < ROWS; row++)
	{
		//�񐔕��J��Ԃ�
		for (int col = 0; col < COLS; col++)
		{

			//1�̎��A�u���b�N����
			if (map[row][col] == 1)
			{
				//�u���b�N�𐶐����āA�L�����N�^�}�l�[�W���ɒǉ�
				CApplication::TaskManager()->Add(
					new CBlock(
						TIPSIZE + TIPSIZE * 2 * col,
						TIPSIZE + TIPSIZE * 2 * row,
						TIPSIZE, TIPSIZE,
						CApplication::Texture()));
			}


			//2�̎��A�v���C���[����
			if (map[row][col] == 2)
			{
				//�J�����p����
				mCdx =
					WINDOW_WIDTH / 4 - (TIPSIZE + TIPSIZE * 2 * col);

				mCdy =
					WINDOW_HEIGHT / 4 - (TIPSIZE + TIPSIZE * 2 * row);

				//�v���C���[�𐶐����āA�L�����N�^�[�}�l�[�W���ɒǉ�
				CApplication::TaskManager()->Add(
					//mpPlayer�Ƀv���C���[�̃C���X�^���X�̃|�C���^����
					mpPlayer =
					new CPlayer2(TIPSIZE + TIPSIZE * 2 * col,
						TIPSIZE + TIPSIZE * 2 * row,
						TIPSIZE, TIPSIZE,
						CApplication::Texture()));
			}


			//3�̎��A�G����
			if (map[row][col] == 3)
			{
				//�G�𐶐����āA�L�����N�^�[�}�l�[�W���ɒǉ�
				CApplication::TaskManager()->Add(
					new CEnemy2(TIPSIZE + TIPSIZE * 2 * col,
						TIPSIZE + TIPSIZE * 2 * row,
						TIPSIZE, TIPSIZE,
						CApplication::Texture()));
			}



			//4�̎��A�܂�Ԃ��|�C���g����
			if (map[row][col] == 4)
			{
				//�܂�Ԃ��|�C���g�𐶐����āA�L�����N�^�}�l�[�W���ɒǉ�
				CApplication::TaskManager()->Add(
					new CPoint(TIPSIZE + TIPSIZE * 2 * col,
						TIPSIZE + TIPSIZE * 2 * row,
						TIPSIZE, TIPSIZE,
						CCharacter::ETag::ETURN));
			}
		}
	}

}



void CGame::Update()
{
	//�X�V�A�ՓˁA�폜�A�`��
	CApplication::TaskManager()->Update();

	CApplication::TaskManager()->Collision();
	
	CApplication::TaskManager()->Delete();

	CameraSet();

	CApplication::TaskManager()->Render();

	CCamera::End();


	//UI
	mpUi->Time(mTime++); //����

	mpUi->Hp(CPlayer2::Hp()); //HP

	mpUi->Enemy(CEnemy2::Num()); //�G�̐�

	mpUi->Render();

}




void CGame::Start()
{
	//�Q�[���̕`��
	CApplication::TaskManager()->Render();

	//UI����
	mpUi->Hp(CPlayer2::Hp());

	mpUi->Enemy(CEnemy2::Num());

	mpUi->Render();

	mpUi->Start();

}




bool CGame::IsOver()
{
	//HP��0�ȉ������茋�ʂ�߂�
	return CPlayer2::Hp() <= 0;
}



void CGame::Over()
{

	CameraSet();

	//�Q�[���̕`��
	CApplication::TaskManager()->Render();

	CCamera::End();

	//UI����
	mpUi->Hp(CPlayer2::Hp());

	mpUi->Enemy(CEnemy2::Num());

	mpUi->Render();

	mpUi->Over();

	
}




bool CGame::IsClear()
{
	//�G�̐���0�ȉ������肷��
	return CEnemy2::Num() <= 0;
}



void CGame::Clear()
{
	CameraSet();

	//�Q�[���̕`��
	CApplication::TaskManager()->Render();

	CCamera::End();

	//UI����
	mpUi->Hp(CPlayer2::Hp());

	mpUi->Enemy(CEnemy2::Num());

	mpUi->Render();

	mpUi->Clear();

}




CGame::~CGame()
{
	//���ׂẴC���X�^���X�폜
	CApplication::TaskManager()->AllDelete();

	//UI�𐶐����Ă���Ƃ�
	if (mpUi != nullptr)
	{
		//UI���폜���A������
		delete mpUi;

		mpUi = nullptr;
	}
}



void CGame::CameraSet()
{
	float x = mpPlayer->X() + mCdx;

	float y = mpPlayer->Y() + mCdy;

	CCamera::Start(x - WINDOW_WIDTH / 4
		, x + WINDOW_WIDTH / 4
		, y - WINDOW_HEIGHT / 4
		, y + WINDOW_HEIGHT / 4);
}


