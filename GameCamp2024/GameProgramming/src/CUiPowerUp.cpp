#include "CUiPowerUp.h"
#include "CPlayer.h"
#include <stdlib.h>
#include "CUiTexture.h"

#define TEX_JUMP_UP 0,120,120,0 //�W�����v��
#define TEX_DEFENSE_UP 120,240,120,0 //�h���
#define TEX_ATTACK_UP 360,240,120,0 //�U����
#define TEX_ATTACK_NUM_UP 0,120,240,120 //�U���i�K����
#define TEX_SPEED_UP 120,240,240,120 //�ړ����x�㏸

#define TEXTURE_YWH 560,100,100 //y,w,h
#define ITEM_ICON 25,25 //w,h

#define JUMP_MAX 3//�W�����v�����̏��
#define DEFENSE_MAX 3//�h�䋭���̏��
#define ATTACK_MAX 5//�U�������̏��
#define ATTACK_NUM_MAX 2//�U���i�K�����̏��
#define SPEED_MAX 3//�ړ����x�����̏��

#define ITEM_POSX 480

//static�ϐ��̒�`
CUiPowerUp* CUiPowerUp::mpInstance1;
CUiPowerUp* CUiPowerUp::mpInstance2;
CUiPowerUp* CUiPowerUp::mpInstance3;
CTexture CUiPowerUp::mTexture;
//���łɑI������Ă��邩�ǂ���
bool CUiPowerUp::isJumpUp;
bool CUiPowerUp::isDefenseUp;
bool CUiPowerUp::isAttackUp;
bool CUiPowerUp::isAttackNumUp;
bool CUiPowerUp::isSpeedUp;
//����������
int CUiPowerUp::mJumpMax;
int CUiPowerUp::mDefenseMax;
int CUiPowerUp::mAttackMax;
int CUiPowerUp::mAttackNumMax;
int CUiPowerUp::mSpeedMax;
//�ő勭���̃A�C�e����
int CUiPowerUp::mMaxItemNum;

//static���\�b�h�̒�`
CUiPowerUp* CUiPowerUp::GetInstance1()
{
	return mpInstance1;
}
CUiPowerUp* CUiPowerUp::GetInstance2()
{
	return mpInstance2;
}
CUiPowerUp* CUiPowerUp::GetInstance3()
{
	return mpInstance3;
}
void CUiPowerUp::SetMaxDefault()
{
	mJumpMax = 0;
	mDefenseMax = 0;
	mAttackMax = 0;
	mAttackNumMax = 0;
	mSpeedMax = 0;
}

//�C���X�^���X�̍폜
void CUiPowerUp::DeleteInstance()
{
	delete mpInstance1;
	delete mpInstance2;
	delete mpInstance3;
	mpInstance1 = nullptr;
	mpInstance2 = nullptr;
	mpInstance3 = nullptr;
	isJumpUp = false;
	isDefenseUp = false;
	isAttackUp = false;
	isAttackNumUp = false;
	isSpeedUp = false;
}

CTexture* CUiPowerUp::GetTexture()
{
	return &mTexture;
}

int CUiPowerUp::GetMaxItem()
{
	mMaxItemNum = 0;
	if (mJumpMax >= JUMP_MAX)
	{
		mMaxItemNum++;
	}
	if (mDefenseMax >= DEFENSE_MAX)
	{
		mMaxItemNum++;
	}
	if (mAttackMax >= ATTACK_MAX)
	{
		mMaxItemNum++;
	}
	if (mAttackNumMax >= ATTACK_NUM_MAX)
	{
		mMaxItemNum++;
	}
	if (mSpeedMax >= SPEED_MAX)
	{
		mMaxItemNum++;
	}
	return mMaxItemNum;
}

CUiPowerUp::CUiPowerUp()
	:CCharacter((int)CTaskPriority::UI)
{
}

CUiPowerUp::CUiPowerUp(float x, int num)
	: CUiPowerUp()
{

	Set(x, TEXTURE_YWH);

	bool isSelect = false;
	while (isSelect == false)
	{
		int Select = rand();//�����_���Ȑ���

        //5�̔{���Ȃ�
		if (Select % 5 == 0)
		{
			if (isJumpUp == false && mJumpMax < JUMP_MAX)
			{
				Texture(GetTexture(), TEX_JUMP_UP);
				isJumpUp = true;
				isSelect = true;
				mItem = EItem::JumpUp;
			}
		}
		//��L�ȊO����4�̔{���Ȃ�
		else if (Select % 4 == 0)
		{
			if (isDefenseUp == false && mDefenseMax < DEFENSE_MAX)
			{
				Texture(GetTexture(), TEX_DEFENSE_UP);
				isDefenseUp = true;
				isSelect = true;
				mItem = EItem::DefenseUp;
			}
		}
		//��L�ȊO����3�̔{���Ȃ�
		else if (Select % 3 == 0)
		{
			if (isAttackUp == false && mAttackMax < ATTACK_MAX)
			{
				Texture(GetTexture(), TEX_ATTACK_UP);
				isAttackUp = true;
				isSelect = true;
				mItem = EItem::AttackUp;
			}
		}
		//��L�ȊO����2�̔{���Ȃ�
		else if (Select % 2 == 0)
		{
			if (isAttackNumUp == false && mAttackNumMax < ATTACK_NUM_MAX)
			{
				Texture(GetTexture(), TEX_ATTACK_NUM_UP);
				isAttackNumUp = true;
				isSelect = true;
				mItem = EItem::AttackNumUp;
			}
		}
		//����ȊO�Ȃ�
		else
		{
			if (isSpeedUp == false && mSpeedMax < SPEED_MAX)
			{
				Texture(GetTexture(), TEX_SPEED_UP);
				isSpeedUp = true;
				isSelect = true;
				mItem = EItem::SpeedUp;
			}
		}
	}

	if (num == 1)
	{
		mpInstance1 = this;
		//�ő勭���̃A�C�e�����ő��ށ|2�����Ȃ�I����3�𐶐�
		if (GetMaxItem() < ITEM_NUM - 2)
		{
			new CUiPowerUp(GetX() + ITEM_POSX * 2, 3);
		}

	}
	else if (num == 2)
	{
		mpInstance2 = this;
		//�ő勭���̃A�C�e�����ő��ށ|1�����Ȃ�I����1�𐶐�
		if (GetMaxItem() < ITEM_NUM - 1)
		{
			new CUiPowerUp(GetX() - ITEM_POSX, 1);
		}
	}
	else if (num == 3)
	{
		mpInstance3 = this;
	}
}

CUiPowerUp::EItem CUiPowerUp::GetItem()
{
	return mItem;
}

void CUiPowerUp::PowerUp()
{
	EItem getItem;
	if (mInput.Key('1'))
	{
		getItem = mpInstance1->GetItem();
	}
	else if (mInput.Key('2'))
	{
		getItem = mpInstance2->GetItem();
	}
	else if (mInput.Key('3'))
	{
		getItem = mpInstance3->GetItem();
	}

	//�W�����v����
	if (getItem == EItem::JumpUp)
	{
		CPlayer::GetInstance()->SetJumpPower();
		mJumpMax++;
		new CUiTexture(ITEM_ICON, CUiTexture::EUiType::Item, TEX_JUMP_UP);
	}
	//�h�䋭��
	else if (getItem == EItem::DefenseUp)
	{
		CPlayer::GetInstance()->SetDeffensePower();
		mDefenseMax++;
		new CUiTexture(ITEM_ICON, CUiTexture::EUiType::Item, TEX_DEFENSE_UP);
	}
	//�U������
	else if (getItem == EItem::AttackUp)
	{
		CPlayer::GetInstance()->SetAttackPower();
		mAttackMax++;
		new CUiTexture(ITEM_ICON, CUiTexture::EUiType::Item, TEX_ATTACK_UP);
	}
	//�U���i�K����
	else if (getItem == EItem::AttackNumUp)
	{
		CPlayer::GetInstance()->SetAttackNumPower();
		mAttackNumMax++;
		new CUiTexture(ITEM_ICON, CUiTexture::EUiType::Item, TEX_ATTACK_NUM_UP);
	}
	//�ړ����x�㏸
	else
	{
		CPlayer::GetInstance()->SetSpeedPower();
		mSpeedMax++;
		new CUiTexture(ITEM_ICON, CUiTexture::EUiType::Item, TEX_SPEED_UP);
	}
}
