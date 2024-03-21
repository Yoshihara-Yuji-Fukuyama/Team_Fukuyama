#pragma once
#include "CTexture.h"
#include "CCharacter.h"
#include "CInput.h"

#define ITEM_NUM 5 //�A�C�e���̎��

class CUiPowerUp :public CCharacter
{
public:
	//�A�C�e���̎��
	enum class EItem
	{
		JumpUp,
		DefenseUp,
		AttackUp,
		AttackNumUp,
		SpeedUp,
	};

	CUiPowerUp();
	CUiPowerUp(float x, int num);

	//�����K�p
	void PowerUp();


	CUiPowerUp::EItem GetItem();
	//static���\�b�h�̐錾
	static CUiPowerUp* GetInstance1();
	static CUiPowerUp* GetInstance2();
	static CUiPowerUp* GetInstance3();
	static void DeleteInstance();
	static CTexture* GetTexture();
	static void SetMaxDefault();	//�f�t�H���g�ɖ߂�
	static int GetMaxItem();//�ő勭���ς݂̐����擾
private:
	CInput mInput;
	EItem mItem;
	//static�ϐ��̐錾
	static CUiPowerUp* mpInstance1;
	static CUiPowerUp* mpInstance2;
	static CUiPowerUp* mpInstance3;
	static CTexture mTexture;
	//�I�΂ꂽ���ǂ���
	static bool isJumpUp;
	static bool isDefenseUp;
	static bool isAttackUp;
	static bool isAttackNumUp;
	static bool isSpeedUp;
	//������
	static int mJumpMax;
	static int mDefenseMax;
	static int mAttackMax;
	static int mAttackNumMax;
	static int mSpeedMax;
	//�ő�܂ŋ���������
	static int mMaxItemNum;
};