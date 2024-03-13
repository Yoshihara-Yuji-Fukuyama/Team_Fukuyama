#pragma once
#include "CCharacter.h"
#include "CCollider.h"
#include "CAnimation.h"

class CEnemy :public CCharacter, public CAnimation
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

	void Collision(CCollider* m, CCollider* o);

	//�A�j���[�V������ݒ�
	void SetAnimation();

	//���S����
	void Death();

	//static���\�b�h�̐錾
	static CTexture* GetTexture();

private:
	//�R���C�_
	CCollider mColider;
	//static�ϐ��̐錾
	static CTexture mTexture;

};