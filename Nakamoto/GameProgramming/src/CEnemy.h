#pragma once
#include "CCharacter.h"
#include "CCollider.h"
#include "CAnimation.h"
#include "CShadow.h"
#include "CAttack.h"

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

	//�A�j���[�V������ݒ�
	void SetAnimation();

	//�U������
	void Attack();

	//���S����
	void Death();

	//�G�̃^�C�v�̎擾
	CEnemy::EEnemyType GetEnemyType();

	/// <summary>
	/// �Փ˔���
	/// </summary>
	/// <param name="m">�R���C�_1</param>
	/// <param name="o">�R���C�_2</param>
	void Collision(CCollider* m, CCollider* o);

	//static���\�b�h�̐錾
	static CTexture* GetTextureSlime();

	static CTexture* GetTextureOni();

	//�G�̐����擾
	static int GetEnemyCount();
	//�G�̐����P���Z
	static void PlusEnemyCount();
	//�G�̐����[���ɂ���
	static void ZeroEnemyCount();

private:
	//�e
	CShadow* mpShadow;
	//�G�̎��
	EEnemyType mEnemyType;
	//�R���C�_
	CCollider mCollider;
	//�t���[���J�E���^
	int mFrame;
	//�����_��
	int RandomX;
	int RandomY;
	int RandomTiming;
	//�R���C�_�̐����t���O
	bool isCollider;
	//���G�J�E���g
	int mInvincible;

	float mPlayerY;

	//static�ϐ��̐錾
	static CTexture mTextureSlime;

	static CTexture mTextureOni;

	static int mEnemyCount;
};