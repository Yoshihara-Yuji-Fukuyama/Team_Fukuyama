#pragma once

class CTaskManager;
class CCollisionManager;

enum class CTaskPriority
{
	Title,    //�^�C�g��
	UI,      //UI
	Object,  //�I�u�W�F�N�g
	Shadow,  //�e
	Field,   //�w�i
	Collider,//�����蔻��
};

class CTask
{
	friend CTaskManager;
	friend CCollisionManager;
public:
	//�f�t�H���g�R���X�g���N�^
	CTask()
		:mpNext(nullptr), mpPrev(nullptr), mpNextObj(nullptr), mpPrevObj(nullptr)
		, mPriority(0), mSortOrder(0), mEnabled(true) {}
	//�f�X�g���N�^
	virtual ~CTask() {}
	//�X�V
	virtual void Update() {}
	//�`��
	virtual void Render() {}
	//�Փ�
	virtual void Collision() {}

protected:
	int mPriority;//�D��x
	int mSortOrder;//��������
	bool mEnabled;//�L���t���O

private:
	CTask* mpNext;//���̃|�C���^
	CTask* mpPrev;//�O�̃|�C���^
	CTask* mpNextObj;//�I�u�W�F�̎��̃|�C���^
	CTask* mpPrevObj;//�I�u�W�F�̑O�̃|�C���^
	CTask* mpNextBackground;//�w�i�̎��̃|�C���^
	CTask* mpPrevBackground;//�w�i�̑O�̃|�C���^
};
