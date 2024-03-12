#pragma once
#include "CCharacter.h"
#include <vector>
/*
　CCharacterクラスのインスタンスを管理する
*/
class CCharacterManager
{
public:
	//全インスタンス削除
	void AllDelete();
	//無効なポインタを削除
	void Delete();

	//衝突判定2
	void Collision();
	//衝突判定4
	void Collision(CCharacter* character);

	//可変長配列の後ろに追加する
	void Add(CCharacter* c);
	//更新
	void Update();
	//描画
	void Render();
private:
	//CCharacterのポインタの可変長配列
	std::vector<CCharacter*>mpCharacters;
};