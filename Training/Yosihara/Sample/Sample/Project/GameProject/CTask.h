#pragma once

class CTaskManager;

enum class CTaskPriority
{
	Field,     //�t�B�[���h
	Shadow,    //�I�u�W�F�N�g�̉e
	Object,    //�Q�[�����̃I�u�W�F�N�g

	UI,        //UI
};

//�^�X�N�N���X
class CTask
{
	friend CTaskManager;
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="priority">�D��x</param>
	CTask(int priority);
	//�f�X�g���N�^
	virtual ~CTask();

	/// <summary>
	/// �D��x��ݒ�
	/// </summary>
	/// <param name="priority">�ݒ肷��D��x</param>
	void SetPriority(int priority);
	/// <summary>
	/// �D��x���擾
	/// </summary>
	/// <returns>�D��x</returns>
	int GetPriority() const;

	/// <summary>
	/// �������Ԃ�ݒ�
	/// </summary>
	/// <param name="order">�ݒ肷�鏈������</param>
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
	/// �L�����ǂ����擾
	/// </summary>
	/// <returns>true�Ȃ�ΗL��</returns>
	bool IsEnable() const;

	/// <summary>
	/// �\�����邩�ǂ�����ݒ�
	/// </summary>
	/// <param name="show">true�Ȃ�Ε\��</param>
	void SetShow(bool show);
	/// <summary>
	/// �\�����邩�ǂ������擾
	/// </summary>
	/// <returns>true�Ȃ�Ε\��</returns>
	bool IsShow() const;
	
	//�^�X�N���폜
	void Kill();
	//�^�X�N�̍폜�t���O�������Ă��邩
	bool IsKill() const;

	//�X�V
	virtual void Update();
	//�`��
	virtual void Render();

private:
	int mPriority;//�^�X�N�̗D��x
	int mSortOrder;//��������
	bool mIsEnable;//�^�X�N���L�����ǂ���
	bool mIsShow;//�^�X�N��`�悷�邩�ǂ���
	bool mIsKill;//�^�X�N�̍폜�t���O
};
