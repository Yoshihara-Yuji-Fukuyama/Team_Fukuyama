#pragma once
#include "CCharacter.h"
#include "CCollider.h"
#include "CShadow.h"

class CHeal :public CCharacter
{
public:
	CHeal();
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="x">X���W</param>
	/// <param name="y">Y���W</param>
	/// <param name="texture">�e�N�X�`���̃|�C���^</param>
	CHeal(float x, float y, CTexture* texture);
	//�f�X�g���N�^
	~CHeal();

	void Update();
	/// <summary>
    /// �Փ˔���
    /// </summary>
    /// <param name="m">�R���C�_1</param>
    /// <param name="o">�R���C�_2</param>
	void Collision(CCollider* m, CCollider* o);

	//static���\�b�h�̐錾
	static CTexture* GetTexture();
private:
	CShadow* mpShadow;
	//�̂̃R���C�_
	CCollider mCollider;

	//static�ϐ��̐錾
	static CTexture mTexture;
};
