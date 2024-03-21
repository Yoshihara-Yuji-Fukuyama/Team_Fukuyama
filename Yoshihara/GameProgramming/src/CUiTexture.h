#pragma once
#include "CCharacter.h"

class CUiTexture :public CCharacter
{
public:
	//UI�̎��
	enum class EUiType
	{
		HpRed,
		HpYellow,
		Frame,
		Face,
		Item,
	};
	//�f�t�H���g�R���X�g���N�^
	CUiTexture();
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="w">��</param>
	/// <param name="h">����</param>
	/// <param name="uiType">UI�̎��</param>
	/// <param name="left">�e�N�X�`���̍�</param>
	/// <param name="right">�e�N�X�`���̉E</param>
	/// <param name="bottom">�e�N�X�`���̉�</param>
	/// <param name="top">�e�N�X�`���̏�</param>
	CUiTexture(float w, float h, EUiType uiType, int left = 0, int right = 0, int bottom = 0, int top = 0);

	//�X�V
	void Update();

	//static���\�b�h�̐錾
	static CTexture* GetTextureHpBar();

	static CTexture* GetTextureFrame();

	static CTexture* GetTextureFace();

	static void SetItemNum();
private:
	//UI�̎��
	EUiType mUiType;
	//���݂�HP
	float mHp;
	//HP�̍ő�l
	float mMaxHp;
	//���̕ۑ�
	float mW;
	//�A�C�e�����ۑ�
	int mItemNumSave;

	//static�ϐ��̐錾
	static CTexture mTextureHpBar;

	static CTexture mTextureFrame;

	static CTexture mTextureFace;

	static int mItemNum;
};