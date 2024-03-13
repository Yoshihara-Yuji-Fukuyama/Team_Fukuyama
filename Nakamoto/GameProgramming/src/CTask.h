#pragma once

class CTaskManager;
class CCollisionManager;

enum class CTaskPriority
{
	SPACE,
	UI,
	Object,
	Field,
	Collider,
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
	CTask* mpNextCollider;//�R���C�_�̎��̃|�C���^
	CTask* mpPrevCollider;//�R���C�_�̑O�̃|�C���^
};
