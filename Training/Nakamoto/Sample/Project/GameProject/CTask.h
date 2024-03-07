#pragma once

class CTaskManager;

//�^�X�N�̗D��x
enum class CTaskPrio
{
	Field,		//�t�B�[���h
	Object,		//�Q�[�����̃I�u�W�F�N�g

	UI,			//��ʂɕ\������HUD�Ȃǂ�UI
};

//�^�X�N�N���X
class CTask
{
	friend CTaskManager;

public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="prio">�D��x</param>
	CTask(int prio);
	//�f�X�g���N�^
	virtual ~CTask();

	/// <summary>
	/// �D��x���擾
	/// </summary>
	/// <param name="prio">�ݒ肷��D��x</param>
	/// <returns></returns>
	void SetPriority(int prio);
	/// <summary>
	/// �D��x�̎擾
	/// </summary>
	/// <returns></returns>
	int GetPriority() const;

	/// <summary>
	/// �D��x��ݒ�
	/// </summary>
	/// <param name="order">�ݒ肷��D��x</param>
	void SetSortOrder(int order);
	/// <summary>
	/// �������Ԃ��擾
	/// </summary>
	/// <returns></returns>
	int GetSortOrder() const;

	/// <summary>
	/// �L�����ǂ�����ݒ�
	/// </summary>
	/// <param name="enable">true�Ȃ�ΗL��</param>
	void SetEnable(bool enable);
	/// <summary>
	/// �L�����ǂ������擾
	/// </summary>
	/// <returns>true�Ȃ�ΗL��</returns>
	bool IsEnable() const;

	/// <summary>
	/// �\�����邩�ǂ�����ݒ�
	/// </summary>
	/// <param name="show">true�Ȃ�Ε\������</param>
	void SetShow(bool show);
	/// <summary>
	/// �\�����邩�ǂ������擾
	/// </summary>
	/// <returns>true�Ȃ�Ε\������</returns>
	bool IsShow() const;

	//�^�X�N���폜
	void Kill();
	//�^�X�N�̍폜�t���O�������Ă��邩
	bool IsKill();

	//�X�V
	virtual void Update();
	//�`��
	virtual void Render();
private:
	int mPrio;		//�^�X�N�̗D��x
	int mSortOrder; //�����D��x���̏�������
	bool mIsEnable;	//�^�X�N���L�����ǂ���
	bool mIsShow;	//�^�X�N��`�悷�邩�ǂ���
	bool mIsKill;	//�^�X�N�̍폜�t���O
};