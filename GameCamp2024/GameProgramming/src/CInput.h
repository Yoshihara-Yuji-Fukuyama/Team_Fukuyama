#pragma once
#include <Windows.h>

class CInput
{
public:
	//true: 文字のキーが押されている
	//false:文字のキーが押されていない
	//bool Key(入力キー)
	bool Key(char key);
};