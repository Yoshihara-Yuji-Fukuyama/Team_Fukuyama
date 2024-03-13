#include "CBackground.h"
#include "CGame.h"

//�萔�̒�`
#define TEX_COORD_BACKGROUND 0,1920,1080,0   //�e�N�X�`���}�b�s���O
#define BACKGROUND_POSX 3840.0f              //���̎��̔w�i�������������W�̉����Z�p���l

//static�ϐ��̒�`
CTexture CBackground::mTexture;

//���\�b�h�̒�`
CTexture* CBackground::GetTexture()
{
	return &mTexture;
}

//�w�i�̃f�t�H���g�R���X�g���N�^
CBackground::CBackground()
	:CCharacter((int)CTaskPriority::Field)
{
}
//�w�i�̃R���X�g���N�^
CBackground::CBackground(float x, float y, float w, float h,
	CBackground* next2, CBackground* prev2)
	: CBackground()
{
	Set(x, y, w, h);

	Texture(GetTexture(), TEX_COORD_BACKGROUND);

	Next2Background = next2;
	Prev2Background = prev2;
}

//�X�V
void CBackground::Update()
{
	CreateBackground(this, CPlayer::GetInstance());
	DeleteBackground(this, CPlayer::GetInstance());
}

//�w�i����
void CBackground::CreateBackground(CBackground* background, CPlayer* player)
{
	//�������̔w�i��X���W���v���C���[��X���W��菬����
	//�����̎��̔w�i����������Ă��Ȃ��Ȃ�
	if (background->GetX() < player->GetX() && Next2Background == nullptr)
	{
		//���̎��̔w�i�̐���
		Next2Background = new CBackground(background->GetX() + BACKGROUND_POSX,
			background->GetY(), background->GetW(), background->GetH(), nullptr, this);
	}

	//�������̔w�i��X���W���v���C���[��X���W���傫��
	//���O�̑O�̔w�i����������Ă��Ȃ��Ȃ�
	if (background->GetX() > player->GetX() && Prev2Background == nullptr)
	{
		//�O�̑O�̔w�i�̐���
		Prev2Background = new CBackground(background->GetX() - BACKGROUND_POSX,
			background->GetY(), background->GetW(), background->GetH(), this, nullptr);
	}
}

//�w�i�폜
void CBackground::DeleteBackground(CBackground* background, CPlayer* player)
{
	//�������̔w�i��X���W���v���C���[��X���W��菬����
	//���O�̑O�̔w�i����������Ă���Ȃ�
	if (background->GetX() < player->GetX() && Prev2Background != nullptr)
	{
		//�O�̑O�̔w�i�̍폜
		Prev2Background->SetEnabled(false);
		Prev2Background = nullptr;
	}
	//�������̔w�i��X���W���v���C���[��X���W���傫��
	//�����̎��̔w�i����������Ă���Ȃ�
	if (background->GetX() > player->GetX() && Next2Background != nullptr)
	{
		//���̎��̔w�i�̍폜
		Next2Background->SetEnabled(false);
		Next2Background = nullptr;
	}
}