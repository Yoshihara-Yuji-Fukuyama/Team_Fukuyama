#include "CBackground.h"
#include "CGame.h"
#include "CPlayer.h"

//�萔�̒�`
#define TEX_COORD_BACKGROUND 0,1920,1080,0   //�e�N�X�`���}�b�s���O
#define BACKGROUND_POSX 3840.0f              //���̎��̔w�i�������������W�̉����Z�p���l
#define BACKGROUND_CLOUD_SPEED 0.5f          //�_�̃X�s�[�h
#define BACKGROUND_BUILDING_SPEED 1.0f       //�����̃X�s�[�h

//static�ϐ��̒�`
CTexture CBackground::mTextureSky;
CTexture CBackground::mTextureCloudA;
CTexture CBackground::mTextureCloudB;
CTexture CBackground::mTextureCloudC;
CTexture CBackground::mTextureBuilding;
CTexture CBackground::mTextureRoad;

//���\�b�h�̒�`
CTexture* CBackground::GetTextureSky()
{
	return &mTextureSky;
}
CTexture* CBackground::GetTextureCloudA()
{
	return &mTextureCloudA;
}
CTexture* CBackground::GetTextureCloudB()
{
	return &mTextureCloudB;
}
CTexture* CBackground::GetTextureCloudC()
{
	return &mTextureCloudC;
}
CTexture* CBackground::GetTextureBuilding()
{
	return &mTextureBuilding;
}
CTexture* CBackground::GetTextureRoad()
{
	return &mTextureRoad;
}

//�w�i�̃f�t�H���g�R���X�g���N�^
CBackground::CBackground()
	:CCharacter((int)CTaskPriority::Field)
{
	mVx = CPlayer::GetInstance()->GetmVx();
}
//�w�i�̃R���X�g���N�^
CBackground::CBackground(float x, float y, float w, float h,
	CBackground* next2, CBackground* prev2, int sortOrder, float distanceX)
	: CBackground()
{
	X = distanceX;

	SetSortOrder(sortOrder);

	Set(x, y, w, h);

	//�摜�̐ݒ�
	if (mSortOrder == (int)EFieldSort::Sky)
	{
		Texture(GetTextureSky(), TEX_COORD_BACKGROUND);
	}
	else if (mSortOrder == (int)EFieldSort::CloudA)
	{
		Texture(GetTextureCloudA(), TEX_COORD_BACKGROUND);
	}
	else if (mSortOrder == (int)EFieldSort::CloudB)
	{
		Texture(GetTextureCloudB(), TEX_COORD_BACKGROUND);
	}
	else if (mSortOrder == (int)EFieldSort::CloudC)
	{
		Texture(GetTextureCloudC(), TEX_COORD_BACKGROUND);
	}
	else if (mSortOrder == (int)EFieldSort::Building)
	{
		Texture(GetTextureBuilding(), TEX_COORD_BACKGROUND);
	}
	else
	{
		Texture(GetTextureRoad(), TEX_COORD_BACKGROUND);
	}


	NextBackground = next2;
	PrevBackground = prev2;
}

//�X�V
void CBackground::Update()
{
	CreateBackground(this, CPlayer::GetInstance());
	DeleteBackground(this, CPlayer::GetInstance());


	//�w�i�̑��x����
	//��
	if (mSortOrder == (int)EFieldSort::Sky)
	{
		SetX(CPlayer::GetInstance()->GetX());
	}
	//�_
	else if (mSortOrder == (int)EFieldSort::CloudA || mSortOrder == (int)EFieldSort::CloudB || mSortOrder == (int)EFieldSort::CloudC)
	{
		if (CPlayer::GetInstance()->GetMoveX())
		{
			if (CPlayer::GetInstance()->GetmVx() < 0)
			{
				X = X + BACKGROUND_CLOUD_SPEED;
			}
			else
			{
				X = X - BACKGROUND_CLOUD_SPEED;
			}
		}
		SetX(CPlayer::GetInstance()->GetX() + X);
	}
	//����
	else if (mSortOrder == (int)EFieldSort::Building)
	{
		if (CPlayer::GetInstance()->GetMoveX())
		{
			if (CPlayer::GetInstance()->GetmVx() < 0)
			{
				X = X + BACKGROUND_BUILDING_SPEED;
			}
			else
			{
				X = X - BACKGROUND_BUILDING_SPEED;
			}
		}
		SetX(CPlayer::GetInstance()->GetX() + X);

	}
	//��
	else
	{
	}
}

//�w�i����
void CBackground::CreateBackground(CBackground* background, CPlayer* player)
{
	//�������̔w�i��X���W���v���C���[��X���W��菬����
	//�����̔w�i����������Ă��Ȃ��Ȃ�
	if (background->GetX() < player->GetX() && NextBackground == nullptr)
	{
		if (mSortOrder == (int)EFieldSort::Sky)
		{
			//���̔w�i�̐���
			NextBackground = new CBackground(background->GetX() + BACKGROUND_POSX,
				background->GetY(), background->GetW(), background->GetH(), nullptr, this, (int)EFieldSort::Sky);
		}
		else if (mSortOrder == (int)EFieldSort::CloudA)
		{
			//���̔w�i�̐���
			NextBackground = new CBackground(background->GetX() + BACKGROUND_POSX,
				background->GetY(), background->GetW(), background->GetH(), nullptr, this, (int)EFieldSort::CloudA, 1920);
		}
		else if (mSortOrder == (int)EFieldSort::CloudB)
		{
			//���̔w�i�̐���
			NextBackground = new CBackground(background->GetX() + BACKGROUND_POSX,
				background->GetY(), background->GetW(), background->GetH(), nullptr, this, (int)EFieldSort::CloudB, 1920);
		}
		else if (mSortOrder == (int)EFieldSort::CloudC)
		{
			//���̔w�i�̐���
			NextBackground = new CBackground(background->GetX() + BACKGROUND_POSX,
				background->GetY(), background->GetW(), background->GetH(), nullptr, this, (int)EFieldSort::CloudC, 1920);
		}
		else if (mSortOrder == (int)EFieldSort::Building)
		{
			//���̔w�i�̐���
			NextBackground = new CBackground(background->GetX() + BACKGROUND_POSX,
				background->GetY(), background->GetW(), background->GetH(), nullptr, this, (int)EFieldSort::Building, 1920);
		}
		else
		{
			//���̎��̔w�i�̐���
			NextBackground = new CBackground(background->GetX() + BACKGROUND_POSX,
				background->GetY(), background->GetW(), background->GetH(), nullptr, this, (int)EFieldSort::Road);
		}
	}

	//�������̔w�i��X���W���v���C���[��X���W���傫��
	//���O�̔w�i����������Ă��Ȃ��Ȃ�
	if (background->GetX() > player->GetX() && PrevBackground == nullptr)
	{
		if (mSortOrder == (int)EFieldSort::Sky)
		{
			//�O�̔w�i�̐���
			PrevBackground = new CBackground(background->GetX() - BACKGROUND_POSX,
				background->GetY(), background->GetW(), background->GetH(), this, nullptr, (int)EFieldSort::Sky);
		}
		else if (mSortOrder == (int)EFieldSort::CloudA)
		{
			//�O�̔w�i�̐���
			PrevBackground = new CBackground(background->GetX() - BACKGROUND_POSX,
				background->GetY(), background->GetW(), background->GetH(), this, nullptr, (int)EFieldSort::CloudA, -1920);
		}
		else if (mSortOrder == (int)EFieldSort::CloudB)
		{
			//�O�̔w�i�̐���
			PrevBackground = new CBackground(background->GetX() - BACKGROUND_POSX,
				background->GetY(), background->GetW(), background->GetH(), this, nullptr, (int)EFieldSort::CloudB, -1920);
		}
		else if (mSortOrder == (int)EFieldSort::CloudC)
		{
			//�O�̔w�i�̐���
			PrevBackground = new CBackground(background->GetX() - BACKGROUND_POSX,
				background->GetY(), background->GetW(), background->GetH(), this, nullptr, (int)EFieldSort::CloudC, -1920);
		}
		else if (mSortOrder == (int)EFieldSort::Building)
		{
			//�O�̔w�i�̐���
			PrevBackground = new CBackground(background->GetX() - BACKGROUND_POSX,
				background->GetY(), background->GetW(), background->GetH(), this, nullptr, (int)EFieldSort::Building, -1920);
		}
		else
		{
			//�O�̔w�i�̐���
			PrevBackground = new CBackground(background->GetX() - BACKGROUND_POSX,
				background->GetY(), background->GetW(), background->GetH(), this, nullptr, (int)EFieldSort::Road);
		}
	}
}

//�w�i�폜
void CBackground::DeleteBackground(CBackground* background, CPlayer* player)
{
	//�������̔w�i��X���W���v���C���[��X���W��菬����
	//���O�̔w�i����������Ă���Ȃ�
	if (background->GetX() < player->GetX() && PrevBackground != nullptr)
	{
		//�O�̑O�̔w�i�̍폜
		PrevBackground->SetEnabled(false);
		PrevBackground = nullptr;
	}
	//�������̔w�i��X���W���v���C���[��X���W���傫��
	//�����̔w�i����������Ă���Ȃ�
	if (background->GetX() > player->GetX() && NextBackground != nullptr)
	{
		//���̎��̔w�i�̍폜
		NextBackground->SetEnabled(false);
		NextBackground = nullptr;
	}
}