#pragma once
#include "CCharacter.h"
#include <vector>
/*
�@CCharacter�N���X�̃C���X�^���X���Ǘ�����
*/
class CCharacterManager
{
public:
	//�S�C���X�^���X�폜
	void AllDelete();
	//�����ȃ|�C���^���폜
	void Delete();

	//�Փ˔���2
	void Collision();
	//�Փ˔���4
	void Collision(CCharacter* character);

	//�ϒ��z��̌��ɒǉ�����
	void Add(CCharacter* c);
	//�X�V
	void Update();
	//�`��
	void Render();
private:
	//CCharacter�̃|�C���^�̉ϒ��z��
	std::vector<CCharacter*>mpCharacters;
};