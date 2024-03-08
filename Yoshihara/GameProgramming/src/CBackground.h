#pragma once
#include "CCharacter.h"

class CBackground :public CCharacter
{
public:
	void Update();

	//�w�i�̃f�t�H���g�R���X�g���N�^
	CBackground();

	/// <summary>
	/// �w�i�̃R���X�g���N�^
	/// </summary>
	/// <param name="x">X���W</param>
	/// <param name="y">Y���W</param>
	/// <param name="w">��</param>
	/// <param name="h">����</param>
	CBackground(float x, float y, float w, float h);

	//static���\�b�h�̐錾
	static CTexture* GetTexture();

private:
	//static�ϐ��̐錾
	static CTexture mTexture;
};
