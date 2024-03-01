#pragma once
#include "CCharacter.h"
#include <vector>

//CCharacter�N���X�̃C���X�^���X���Ǘ�����

class CCharacterManager
{

public:

	//�Փˏ���1
	void Collision();

	//�Փˏ���3
	//Collision(�Փˌ��̃|�C���^)
	void Collision(CCharacter* character);

	//Add(CCharacter�̃|�C���^)
	//�ϒ��z��̌��ɒǉ�����
	void Add(CCharacter* c);

	//�ϒ��z��ɂ���|�C���^��Update()�����s���Ă���
	void Update();

	//�ϒ��z��ɂ���|�C���^��Render()�����s���Ă���
	void Render();

	void Delete();

	//�S�C���X�^���X�폜
	void AllDelete();

private:

	//CCharacter�̃|�C���^�̉ϒ��z��
	std::vector<CCharacter*>mpCharacters;
};
