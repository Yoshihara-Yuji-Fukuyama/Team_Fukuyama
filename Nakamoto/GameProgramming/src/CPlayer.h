#pragma once

#include "CCharacter.h"
#include "CInput.h"

#define ENEMY_TEXTURE "�U�R�Q�X���C���Q�ړ�.png"

class CPlayer : public CCharacter
{
public:
	CPlayer();

	/// <summary>
	/// �v���C���[��ݒ�
	/// </summary>
	/// <param name="x">X���W</param>
	/// <param name="y">Y���W</param>
	/// <param name="w">��</param>
	/// <param name="h">����</param>
	/// <param name="pt">�e�N�X�`���̃|�C���^</param>
	CPlayer(float x, float y,float w ,float h, CTexture* pt);

	//�X�V����
	void Update();

private:
	CInput mInput;
};