#pragma once

class CTaskManager;
class CCollisionManager;

enum class CTaskPriority
{
	UI,
	Object,
	Field,
};

class CTask
{
	friend CTaskManager;
	friend CCollisionManager;
public:
	//�f�t�H���g�R���X�g���N�^
	CTask()
		:mpNext(nullptr), mpPrev(nullptr), mPriority(0), mEnabled(true) {}
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
	bool mEnabled;//�L���t���O
private:
	CTask* mpNext;//���̃|�C���^
	CTask* mpPrev;//�O�̃|�C���^
};