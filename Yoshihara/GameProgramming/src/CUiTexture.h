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
	};
	//�f�t�H���g�R���X�g���N�^
	CUiTexture();
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="w">��</param>
	/// <param name="h">����</param>
	/// <param name="uiType">UI�̎��</param>
	CUiTexture(float w, float h, EUiType uiType);

	//�X�V
	void Update();

	//static���\�b�h�̐錾
	static CTexture* GetTextureHpBar();

	static CTexture* GetTextureFrame();

	static CTexture* GetTextureFace();
private:
	//UI�̎��
	EUiType mUiType;
	//���݂�HP
	float mHp;
	//HP�̍ő�l
	float mMaxHp;
	//���̕ۑ�
	float mW;

	//static�ϐ��̐錾
	static CTexture mTextureHpBar;

	static CTexture mTextureFrame;

	static CTexture mTextureFace;
};