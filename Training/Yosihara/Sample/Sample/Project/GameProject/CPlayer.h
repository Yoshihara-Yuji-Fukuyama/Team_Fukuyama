#pragma once

class CPlayer
{
//�A�N�Z�X�C���q
//�����ȊO�̊O������A�N�Z�X������
public:
	//�R���X�g���N�^
	CPlayer();
	//�f�X�g���N�^
	~CPlayer();

	/// <summary>
	/// �v���C���[�̍��W���擾
	/// </summary>
	/// <returns>�v���C���[�̍��W</returns>
	const CVector2D& GetPos() const;

	/// <summary>
	/// �v���C���[�̍��W��ݒ�
	/// </summary>
	/// <param name="pos">�ݒ肷����W</param>
	void SetPos(const CVector2D& pos);

	//�X�V����
	void Update();
	//�`�揈��
	void Render();

//�������g�̃N���X�����A�N�Z�X�ł��Ȃ�
//�����o�ϐ��͊�{private
private:
	CVector2D mPos;//�v���C���[�̍��W
	TexAnimData* mpAnimData;//�A�j���[�V�����̃f�[�^
	CImage* mpImage;//�v���C���[�̉摜
	int mHp;//�v���C���[��HP

};
