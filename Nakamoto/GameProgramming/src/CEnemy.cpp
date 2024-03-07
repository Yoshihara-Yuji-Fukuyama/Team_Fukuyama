#include "CEnemy.h"

#define TEX_COORD 0,1525,1078,0//テクスチャマッピング

CEnemy::CEnemy(float x, float y, float w, float h, CTexture* pt)
{
	Set(x, y, w, h);

	Texture(pt, TEX_COORD);
}
