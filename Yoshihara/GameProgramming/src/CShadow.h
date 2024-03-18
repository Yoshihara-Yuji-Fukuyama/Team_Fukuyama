#pragma once
#include "CCharacter.h"

class CShadow :public CCharacter
{
public:
	//�f�t�H���g�R���X�g���N�^
	CShadow();
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="parent">�e</param>
	/// <param name="w">��</param>
	/// <param name="h">����</param>
	CShadow(float x, float y, float w, float h);

	//���W�ݒ�
	void SetShadow(float x, float y, float w, float h);

	//static���\�b�h�̐錾
	static CTexture* GetTexture();
	
private:
	CCharacter* mpParent;

	//static�ϐ��̐錾
	static CTexture mTexture;
};
