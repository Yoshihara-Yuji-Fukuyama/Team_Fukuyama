#pragma once
#include "CCharacter.h"

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
	CEnemy(float x, float y, float w, float h,CTexture* pt);

private:

};