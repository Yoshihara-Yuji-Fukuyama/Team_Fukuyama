#pragma once
#include "CCharacter.h"
#include "CCollider.h"
#include "CAnimation.h"
#include "CShadow.h"

class CEnemy :public CCharacter, public CAnimation
{
public:
	enum class EEnemyType//�G�^�C�v
	{
		Slime,      //�X���C��
		Oni,        //�S
	};

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
	/// <param name="hp">HP</param>
	/// <param name="enemyType">�G�̎��</param>
	CEnemy(float x, float y, float w, float h, int hp, EEnemyType enemyType);

	//�f�X�g���N�^
	~CEnemy();

	//�ړ�����
	void Move();

	void Collision(CCollider* m, CCollider* o);

	//�A�j���[�V������ݒ�
	void SetAnimation();

	//���S����
	void Death();

	//static���\�b�h�̐錾
	static CTexture* GetTextureSlime();

	static CTexture* GetTextureOni();

	//�G�̐����擾
	static int GetEnemyCount();
	//�G�̐����P���Z
	static void PlusEnemyCount();

private:
	CShadow* mpShadow;
	//�G�̎��
	EEnemyType mEnemyType;
	//�R���C�_
	CCollider mColider;
	//�t���[���J�E���^
	int mFrame;
	//�����_��
	int RandomX;
	int RandomY;
	int RandomTiming;

	//static�ϐ��̐錾
	static CTexture mTextureSlime;

	static CTexture mTextureOni;

	static int mEnemyCount;

};