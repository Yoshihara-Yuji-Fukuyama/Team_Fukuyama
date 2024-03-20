#include <stdio.h>
#include "CUiFont.h"

#define FONT "Font.png"         //�t�H���g�̉摜
#define TIME_SIZE 800,1010,20,20//���ԕ\���̃T�C�Y
#define SCORE_SIZE 220,1010,20,20//�X�R�A�T�C�Y
#define SCORE_SIZE_END1 560,700,100,100 //�I����̃X�R�A�̃T�C�Y
#define SCORE_SIZE_END2 710,400,50,50   //�I����̃X�R�A�̐��l�̃T�C�Y

#define TIME_MAX 180 //�ő厞��

//static�ϐ��̐錾
CUiFont* CUiFont::mpInstance;

//static���\�b�h�̐錾
CUiFont* CUiFont::GetInstance()
{
	if (mpInstance == nullptr)
	{
		mpInstance = new CUiFont();
	}
	return mpInstance;
}

void CUiFont::DeleteInstance()
{
	if (mpInstance != nullptr)
	{
		delete mpInstance;
		mpInstance = nullptr;
	}
}

//�f�t�H���g�R���X�g���N�^
CUiFont::CUiFont()
	:mTime(TIME_MAX)
	, mScore(0)
{
	mFont.Load(FONT, 1, 64);
}

void CUiFont::SetTime()
{
	mTime = mTime--;
}

int CUiFont::GetTime()
{
	return mTime;
}

void CUiFont::SetScore(int score)
{
	mScore = mScore + score;
}

void CUiFont::Render()
{
	char str[16];

	//����
	sprintf(str, "TIME:%03d", mTime);
	mFont.Draw(TIME_SIZE, str);
	//�X�R�A
	sprintf(str, "SCORE:%06d", mScore);
	mFont.Draw(SCORE_SIZE, str);
}

void CUiFont::EndRender()
{
	char str[16];

	//�X�R�A
	sprintf(str, "SCORE");
	mFont.Draw(SCORE_SIZE_END1, str);

	//�X�R�A���l
	sprintf(str, "%06d", mScore);
	mFont.Draw(SCORE_SIZE_END2, str);
}
