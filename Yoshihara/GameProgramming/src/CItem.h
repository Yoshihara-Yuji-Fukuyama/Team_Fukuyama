#pragma once
#include "CCharacter.h"
#include "CCollider.h"

class CItem :public CCharacter
{
public:
	CItem();
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="x">X���W</param>
	/// <param name="y">Y���W</param>
	/// <param name="w">��</param>
	/// <param name="h">����</param>
	/// <param name="texture">�e�N�X�`���̃|�C���^</param>
	CItem(float x, float y, float w, float h, CTexture* texture);

	/// <summary>
    /// �Փ˔���
    /// </summary>
    /// <param name="m">�R���C�_1</param>
    /// <param name="o">�R���C�_2</param>
	void Collision(CCollider* m, CCollider* o);

	//static���\�b�h�̐錾
	static CTexture* GetTexture();
private:
	//�̂̃R���C�_
	CCollider mCollider;

	//static�ϐ��̐錾
	static CTexture mTexture;
};
