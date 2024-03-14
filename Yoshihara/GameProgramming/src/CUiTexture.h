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
		Player,
	};
	//�f�t�H���g�R���X�g���N�^
	CUiTexture();
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="x">X���W</param>
	/// <param name="y">Y���W</param>
	/// <param name="w">��</param>
	/// <param name="h">����</param>
	/// <param name="uiType">UI�̎��</param>
	CUiTexture(float x, float y, float w, float h, EUiType uiType);

	//static���\�b�h�̐錾
	static CTexture* GetTextureHpBar();

	static CTexture* GetTextureFrame();

	static CTexture* GetTextureFace();
private:
	//UI�̎��
	EUiType mUiType;

	//static�ϐ��̐錾
	static CTexture mTextureHpBar;

	static CTexture mTextureFrame;

	static CTexture mTextureFace;
};