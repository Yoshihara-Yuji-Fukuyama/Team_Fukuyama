#pragma once
#include "CTexture.h"

class CFont
{
public:
	/// <summary>
	/// �e�N�X�`�������[�h
	/// </summary>
	/// <param name="file">�t�@�C����</param>
	/// <param name="row">�s��</param>
	/// <param name="col">��</param>
	void Load(const char* file, int row, int col);

	/// <summary>
	/// �`��
	/// </summary>
	/// <param name="x">X���W</param>
	/// <param name="y">Y���W</param>
	/// <param name="w">��</param>
	/// <param name="h">����</param>
	/// <param name="c">����</param>
	void Draw(float x, float y, float w, float h, char c);

	/// <summary>
	/// �`��
	/// </summary>
	/// <param name="x">X���W</param>
	/// <param name="y">Y���W</param>
	/// <param name="w">��</param>
	/// <param name="h">����</param>
	/// <param name="c">������</param>
	void Draw(float x, float y, float w, float h, char c[]);

private:
	CTexture mTexture;
};
