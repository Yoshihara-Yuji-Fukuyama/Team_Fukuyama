#pragma once
#include "CCharacter.h"

//�萔�̒�`
#define TEXTURE "ge-mu.png"

class CEnemy :public CCharacter
{
public:
	void Update();

	/// <summary>
	/// �G�̃R���X�g���N�^
	/// </summary>
	/// <param name="x">X���W</param>
	/// <param name="y">Y���W</param>
	/// <param name="w">��</param>
	/// <param name="h">����</param>
	/// <param name="pt">�e�N�X�`���̃|�C���^</param>
	CEnemy(float x, float y, float w, float h, CTexture* pt);

private:


	CEnemy(float x, float y, float w, float h, CTexture* pt);

};