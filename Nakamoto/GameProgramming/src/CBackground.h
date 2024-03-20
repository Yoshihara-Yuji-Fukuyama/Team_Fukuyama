#pragma once
#include "CCharacter.h"
#include "CPlayer.h"
#include"CInput.h"

enum class EFieldSort
{
	Road,
	Building,
	CloudC,
	CloudB,
	CloudA,
	Sky,
};

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
		CBackground* next2, CBackground* prev2, int sortOrder, float distanceX = 0);

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
	static CTexture* GetTextureSky();
	static CTexture* GetTextureCloudA();
	static CTexture* GetTextureCloudB();
	static CTexture* GetTextureCloudC();
	static CTexture* GetTextureBuilding();
	static CTexture* GetTextureRoad();

private:
	float X;//�w�i��X���W�v�Z�p
	CInput mInput;
	CBackground* NextBackground;//���̎��̔w�i�̃|�C���^
	CBackground* PrevBackground;//�O�̑O�̔w�i�̃|�C���^

	//static�ϐ��̐錾
	static CTexture mTextureSky;
	static CTexture mTextureCloudA;
	static CTexture mTextureCloudB;
	static CTexture mTextureCloudC;
	static CTexture mTextureBuilding;
	static CTexture mTextureRoad;
};
