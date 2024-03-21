#include "CInput.h"

bool CInput::Key(char key)
{
	return GetAsyncKeyState(key) < 0;
}