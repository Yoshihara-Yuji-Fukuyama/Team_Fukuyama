#pragma once

class CSlime
{
	//�A�N�Z�X�C���q
	//�����ȊO�̊O������A�N�Z�X������
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="type">�X���C���̎��</param>
	/// <param name="pos">�����ʒu</param>
	CSlime(int type, const CVector2D& pos);
	//�f�X�g���N�^
	~CSlime ();

	/// <summary>
	/// ���W���擾
	/// </summary>
	/// <returns>���W</returns>
	const CVector2D& GetPos() const;

	/// <summary>
	/// ���W��ݒ�
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
	CImage* mpImage;//�摜
	int mHp;//HP
	int mType;//�X���C���̎��
};