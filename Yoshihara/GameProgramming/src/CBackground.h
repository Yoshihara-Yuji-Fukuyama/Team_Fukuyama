#pragma once
#include "CCharacter.h"
#include "CPlayer.h"

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
	/// <param name="next">���̎��̔w�i�̃|�C���^</param>
	/// <param name="prev">�O�̑O�̔w�i�̃|�C���^</param>
	CBackground(float x, float y, float w, float h,
		CBackground* next2, CBackground* prev2);

	/// <summary>
	/// �w�i����
	/// </summary>
	/// <param name="background">�w�i�̃|�C���^</param>
	/// <param name="player">�v���C���[�̃|�C���^</param>
	void CreateBackground(CBackground* background, CPlayer* player);
	/// <summary>
	/// �w�i�폜
	/// </summary>
	/// <param name="background">�w�i�̃|�C���^</param>
	/// <param name="player">�v���C���[�̃|�C���^</param>
	void DeleteBackground(CBackground* background, CPlayer* player);

	//static���\�b�h�̐錾
	static CTexture* GetTexture();

private:
	CBackground* Next2Background;//���̎��̔w�i�̃|�C���^
	CBackground* Prev2Background;//�O�̑O�̔w�i�̃|�C���^

	//static�ϐ��̐錾
	static CTexture mTexture;
};
