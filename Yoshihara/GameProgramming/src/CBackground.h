#pragma once
#include "CCharacter.h"

class CBackground :public CCharacter
{
public:
	void Update();

	/// <summary>
	/// �w�i�̃R���X�g���N�^
	/// </summary>
	/// <param name="x">X���W</param>
	/// <param name="y">Y���W</param>
	/// <param name="w">��</param>
	/// <param name="h">����</param>
	/// <param name="pt">�e�N�X�`���̃|�C���^</param>
	CBackground(float x, float y, float w, float h,CTexture* pt);

private:

};
