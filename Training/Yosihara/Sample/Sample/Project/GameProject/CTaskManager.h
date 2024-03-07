#pragma once
#include <list>

class CTask;

//�^�X�N���Ǘ�����N���X
class CTaskManager
{
public:
	/// <summary>
	/// �^�X�N�����X�g�ɒǉ�
	/// </summary>
	/// <param name="add">�ǉ�����^�X�N</param>
	/// <param name="isSort">�\�[�g���̌Ăяo�����ǂ���</param>
	static void Add(CTask* add, bool isSort = false);
	/// <summary>
	/// �^�X�N�����X�g�����菜��
	/// </summary>
	/// <param name="remove">��菜���^�X�N�̃|�C���^�\</param>
	/// <param name="isSort">�\�[�g���̌Ăяo�����ǂ���</param>
	static void Remove(CTask* remove, bool isSort = false);

	/// <summary>
	/// �^�X�N���폜
	/// </summary>
	/// <param name="del">�폜����^�X�N�̃|�C���^�[</param>
	static void Delete(CTask* del);
	//���X�g���̃^�X�N�����ׂč폜
	static void DeleteAll();

	//���X�g���̑S�^�X�N�̍X�V�������Ăяo��
	static void Update();
	//���X�g���̑S�^�X�N�̕`�揈�����Ăяo��
	static void Render();
private:
	//�R���X�g���N�^
	CTaskManager();
	//�f�X�g���N�^
	~CTaskManager();

	//���ݐ�������Ă���^�X�N�̃��X�g
	static std::list<CTask*> mTaskList;
	//���ݐ�������Ă���I�u�W�F�N�g�̃��X�g
	static std::list<CTask*> mObjectList;
};