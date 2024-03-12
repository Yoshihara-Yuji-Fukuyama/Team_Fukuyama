#pragma once
#include "CCharacter.h"

class CEnemy :public CCharacter
{
public:
	//�X�V����
	void Update() override;

	//�f�t�H���g�R���X�g���N�^
	CEnemy();

	/// <summary>
	/// �G�̃R���X�g���N�^
	/// </summary>
	/// <param name="x">X���W</param>
	/// <param name="y">Y���W</param>
	/// <param name="w">��</param>
	/// <param name="h">����</param>
	CEnemy(float x, float y, float w, float h);

	//�f�X�g���N�^
	~CEnemy();

	//�ړ��A�j���[�V����
	void MoveAnimation();

	//�ҋ@�A�j���[�V����
	void WaitAnimation();

	//���S����
	void Death();

	//static���\�b�h�̐錾
	static CTexture* GetTexture();

private:
	//�t���[���J�E���^
	int mFrame;
	//1�R�}�̃t���[����
	int mFps;
	//static�ϐ��̐錾
	static CTexture mTexture;

};