#pragma once

#include "CCharacter.h"
#include "CInput.h"
#include "CCollider.h"

class CPlayer : public CCharacter
{
public:
	//�f�t�H���g�R���X�g���N�^
	CPlayer();
	//�R���X�g���N�^
	CPlayer(float x, float y, float w, float h);
	//�f�X�g���N�^
	~CPlayer();
	//�X�V����
	void Update();
	
	/// <summary>
	/// �Փˏ���
	/// </summary>
	/// <param name="m">�R���C�_1</param>
	/// <param name="o">�R���C�_2</param>
	void Collision(CCollider* m,CCollider* o);
	//�D��x�̕ύX
	void ChengePriority();

	//static���\�b�h�̐錾
	static CTexture* GetTexture();

private:
	CInput mInput;
	float mJump;		//�W�����v����

	CCollider mCollider;	//�R���C�_�[

	//static�ϐ��̐錾
	static CTexture mTexture;
};