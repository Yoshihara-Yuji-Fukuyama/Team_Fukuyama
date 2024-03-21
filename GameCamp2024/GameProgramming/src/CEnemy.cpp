#include "CEnemy.h"
#include "CPlayer.h"
#include "CUiFont.h"
#include "CHeal.h"

//確認用 削除予定
#include <iostream>

//左、右
//左向き
#define TEX_LEFT1 0,600
#define TEX_LEFT2 600,1200
#define TEX_LEFT3 1200,1800
#define TEX_LEFT4 1800,2400
#define TEX_LEFT5 2400,3000
#define TEX_LEFT6 3000,3600
//右向き
#define TEX_RIGHT1 600,0
#define TEX_RIGHT2 1200,600
#define TEX_RIGHT3 1800,1200
#define TEX_RIGHT4 2400,1800
#define TEX_RIGHT5 3000,2400
#define TEX_RIGHT6 3600,3000
//下、上
//移動
#define TEX_MOVE 1200,600
//待機
#define TEX_WAIT 1800,1200
//攻撃
#define TEX_ATTACK 600,0
//攻撃を受けたとき
#define TEX_HIT 2400,1800

#define KNOCKBACK 50	//ノックバック
#define DAMAGE1 20		//受けるダメージ量
#define DAMAGE2 30		//受けるダメージ量
#define DAMAGE3 50		//受けるダメージ量
#define INVINCIBLE 55	//無敵カウント

#define SLIME_BOTTOM 60                    //スライム足元計算用
#define ONI_BOTTOM 240                      //鬼足元計算用 

#define SLIME_SHADOW_WAIT 20               //スライムの待機中の影高さ計算用
#define SLIME_SHADOW_MOVE 40               //スライムの移動中の影高さ計算用
#define SLIME_SHADOW_ATTACK 80             //スライムの攻撃中の影高さ計算用

#define SLIME_SHADOW_SIZE_WAIT 200,180      //スライムの待機中の影の大きさ
#define SLIME_SHADOW_SIZE_MOVE 200,180      //スライムの移動中の影の大きさ
#define SLIME_SHADOW_SIZE_ATTACK 200,180    //スライムの攻撃中の影の大きさ

#define ONI_SHADOW_WAIT 200               //鬼の待機中の影高さ計算用
#define ONI_SHADOW_MOVE 200               //鬼の移動中の影高さ計算用
#define ONI_SHADOW_ATTACK 220             //鬼の攻撃中の影高さ計算用

#define ONI_SHADOW_SIZE_WAIT 200,100      //鬼の待機中の影の大きさ
#define ONI_SHADOW_SIZE_MOVE 200,100      //鬼の移動中の影の大きさ
#define ONI_SHADOW_SIZE_ATTACK 220,100    //鬼の攻撃中の影の大きさ

//敵の移動速度
#define VELOCITY_ENEMY_X 2.0f                
#define VELOCITY_ENEMY_Y 1.0f
//敵の撃破ポイント
#define SLIME_POINT 1000
#define ONI_POINT 2000

//static変数の定義
CTexture CEnemy::mTextureSlime;
CTexture CEnemy::mTextureOni;
int CEnemy::mEnemyCount = 0;

//メソッドの定義
CTexture* CEnemy::GetTextureSlime()
{
	return &mTextureSlime;
}

CTexture* CEnemy::GetTextureOni()
{
	return &mTextureOni;
}

int CEnemy::GetEnemyCount()
{
	return mEnemyCount;
}

void CEnemy::ZeroEnemyCount()
{
	mEnemyCount = 0;
}

void CEnemy::PlusEnemyCount()
{
	mEnemyCount++;
}

//敵のデフォルトコンストラクタ
CEnemy::CEnemy()
	:CCharacter((int)CTaskPriority::Object)
	, mFrameMove(0)
	, mInvincible(0)
	//敵がプレイヤーに近づける距離
	, RandomX(rand() % 50 + 10)//10から60未満まででランダム
	, RandomY(rand() % 30 + 30)//30から60未満まででランダム
	//行動の間隔
	, RandomTiming(rand() % 100 + 150)//250から500未満まででランダム
	, isCollider(false)
{
	isAttack = false;
	isHit = false;
}

//敵のコンストラクタ
CEnemy::CEnemy(float x, float y, float w, float h, int hp, EEnemyType enemyType)
	:CEnemy()
{
	Set(x, y, w, h);

	SetHp(hp);

	mState = EState::EWAIT;

	mVx = VELOCITY_ENEMY_X;

	mVy = VELOCITY_ENEMY_Y;

	mEnemyType = enemyType;
	//スライムなら
	if (mEnemyType == EEnemyType::Slime)
	{
		//スライムの画像
		Texture(GetTextureSlime(), TEX_LEFT1, TEX_WAIT);
		//足元計算用にスライムを入れる
		mLeg = SLIME_BOTTOM;	
		
		//攻撃アニメーション数+1
		AttackNum = 5;
		//移動アニメーション数
		MoveNum = 4;
		//待機アニメーション数
		WaitNum = 4;
		//攻撃を受けた時のアニメーション数+1
		HitNum = 2;

		//足元設定
		SetZ(GetY() - mLeg);
		//スライムのコライダの生成
		mCollider.SetCollider(this, &mX, &mY, &mZ, 140, 90, CCollider::EColliderType::ESLIME);

		printf("スライムのコライダー生成\n");//確認用 削除予定

		//スライムの影
		mpShadow = new CShadow(GetX(), GetShadowPosY(), SLIME_SHADOW_SIZE_WAIT);
	}
	//鬼なら
	if (mEnemyType == EEnemyType::Oni)
	{
		//鬼の画像
		Texture(GetTextureOni(), TEX_LEFT1, TEX_WAIT);
		//足元計算用に鬼を入れる
		mLeg = ONI_BOTTOM;

		//攻撃アニメーション数+1
		AttackNum = 7;
		//移動アニメーション数
		MoveNum = 5;
		//待機アニメーション数
		WaitNum = 4;
		//攻撃を受けた時のアニメーション数+1
		HitNum = 2;

		//足元設定
		SetZ(GetY() - mLeg);
		//鬼のコライダの生成
		mCollider.SetCollider(this, &mX, &mY, &mZ, 80, 200, CCollider::EColliderType::EONI);

		printf("鬼のコライダー生成\n");//確認用 削除予定

		//鬼の影
		mpShadow = new CShadow(GetX(), GetShadowPosY(), ONI_SHADOW_SIZE_WAIT);
	}

}

void CEnemy::Update()
{
	//離れた敵は消去する
	if (CPlayer::GetInstance()->GetX() - GetX() > 1920 || CPlayer::GetInstance()->GetX() - GetX() < -1920)
	{
		SetEnabled(false);
	}
	//処理順番を決定
	SetSortOrder(GetY() - mLeg);
	switch (mState)
	{
	case EState::EWAIT://待機
		
		if (mEnemyType == EEnemyType::Slime)
		{
			//影の高さ
			mShadow = SLIME_SHADOW_WAIT;
			//影の大きさ
			mpShadow->SetShadow(GetX(), GetShadowPosY(), SLIME_SHADOW_SIZE_WAIT);
		}
		else
		{
			//影の高さ
			mShadow = ONI_SHADOW_WAIT;
			//影の大きさ
			mpShadow->SetShadow(GetX(), GetShadowPosY(), ONI_SHADOW_SIZE_WAIT);
		}


		//移動できるようになるとステータスが移動になる
		Move();
		//待機アニメーション
		WaitAnimation(WaitNum);
		//アニメーションを設定
		SetAnimation();

		if (isHit == true)
		{
			mState = EState::EHIT;
			mFrame = 0;
		}
		else if (isAttack == true)
		{
			//状態を攻撃に変更
			mState = EState::EATTACK;
			mFrame = 0;
		}

		break;
		
	case EState::EMOVE://移動

		if (mEnemyType == EEnemyType::Slime)
		{
			//影の高さ
			mShadow = SLIME_SHADOW_MOVE;
			//影の大きさ
			mpShadow->SetShadow(GetX(), GetShadowPosY(), SLIME_SHADOW_SIZE_MOVE);
		}
		else
		{
			//影の高さ
			mShadow = ONI_SHADOW_MOVE;
			//影の大きさ
			mpShadow->SetShadow(GetX(), GetShadowPosY(), ONI_SHADOW_SIZE_MOVE);
		}

		//移動処理
		Move();

		//移動アニメーション
		MoveAnimation(GetX(), GetY(), isMoveX, isMoveY, mVx, MoveNum);
		//アニメーションを設定
		SetAnimation();

		if (isHit == true)
		{
			mState = EState::EHIT;
			mFrame = 0;
		}
		else if (isAttack == true)
		{
			//状態を攻撃に変更
			mState = EState::EATTACK;
			mFrame = 0;
		}


		break;

	case EState::EATTACK: //攻撃

		if (mEnemyType == EEnemyType::Slime)
		{
			//影の高さ
			mShadow = SLIME_SHADOW_ATTACK;
			//影の大きさ
			mpShadow->SetShadow(GetX(), GetShadowPosY(), SLIME_SHADOW_SIZE_ATTACK);
		}
		else
		{
			//影の高さ
			mShadow = ONI_SHADOW_ATTACK;
			//影の大きさ
			mpShadow->SetShadow(GetX(), GetShadowPosY(), ONI_SHADOW_SIZE_ATTACK);
		}

		AttackAnimation(AttackNum);

		//アニメーションを設定
		SetAnimation();

		if (mEnemyType == EEnemyType::Slime)
		{
			if (isAttack == true && isCollider == true && mAnimationNum == CAnimationNumber::Move4)
			{
				Attack();
				isCollider = false;
			}

		}
		else if (mEnemyType == EEnemyType::Oni)
		{
			if (isAttack == true && isCollider == true && mAnimationNum == CAnimationNumber::Move3)
			{
				Attack();
				isCollider = false;
			}
		}

		if (isHit == true)
		{
			mState = EState::EHIT;
			isAttack = false;
			isCollider = false;
			mFrame = 0;
		}
		else if (isAttack == false)
		{
			mState = EState::EWAIT;
			mFrame = 0;
		}

		break;

	case EState::EHIT:
		if (mEnemyType == EEnemyType::Slime)
		{
			//影の高さ
			mShadow = SLIME_SHADOW_ATTACK;
			//影の大きさ
			mpShadow->SetShadow(GetX(), GetShadowPosY(), SLIME_SHADOW_SIZE_ATTACK);
		}
		else
		{
			//影の高さ
			mShadow = ONI_SHADOW_ATTACK;
			//影の大きさ
			mpShadow->SetShadow(GetX(), GetShadowPosY(), ONI_SHADOW_SIZE_ATTACK);
		}

		HitAnimation(HitNum);
		//アニメーションを設定
		SetAnimation();


		if (isHit == false)
		{
			mState = EState::EWAIT;
			isCollider = false;
		}

		break;
	}

	//無敵時間
	if (mInvincible > 0)
	{
		//無敵時間中減算
		mInvincible--;
	}

	//HPが0なら削除
	if (mHp <= 0)
	{
		Death();
	}

	//奥行が同じになったら少しずらす
	if (CPlayer::GetInstance()->GetZ() == GetZ())
	{
		SetY(GetY() + 2);
	}

}

void CEnemy::Move()
{
	const int MoveInterval = 250;
	int frame = mFrameMove++;
	int move;


	//frame/MoveIntervalのあまりがRandomTimingの倍数ならかつ攻撃を受けていないなら
	if (frame % MoveInterval % RandomTiming == 0 && isHit == false)
	{
			mState = EState::EMOVE;
	}

	//ステータスが移動なら移動処理
	if (mState == EState::EMOVE)
	{
		//プレイヤーが右にいるなら右に移動
		if (CPlayer::GetInstance()->GetX() - GetX() > RandomX)
		{
			//mVxが負の数なら正数にする
			if (mVx < 0)
			{
				mVx = -mVx;
			}
			SetX(GetX() + mVx);
			isMoveX = true;
			isMove = true;
		}
		//プレイヤーが左にいるなら左に移動
		else if (CPlayer::GetInstance()->GetX() - GetX() < -RandomX)
		{
			//mVxが正数なら負の数にする
			if (mVx > 0)
			{
				mVx = -mVx;
			}
			SetX(GetX() + mVx);
			isMoveX = true;
			isMove = true;
		}
		else
		{
			isMoveX = false;
		}
		//プレイヤーが上にいるなら上に移動
		if (CPlayer::GetInstance()->GetUnderPosY() - GetUnderPosY() > RandomY)
		{
			//mVyが負の数なら正数にする
			if (mVy < 0)
			{
				mVy = -mVy;
			}
			SetY(GetY() + mVy);
			SetZ(GetY() - mLeg);
			isMoveY = true;
			isMove = true;
		}
		//プレイヤーが下にいるなら下に移動
		else if (CPlayer::GetInstance()->GetUnderPosY() - GetUnderPosY() < -RandomY)
		{
			//mVyが正数なら負の数にする
			if (mVy > 0)
			{
				mVy = -mVy;
			}
			SetY(GetY() + mVy);
			SetZ(GetY() - mLeg);
			isMoveY = true;
			isMove = true;
		}
		else
		{
			isMoveY = false;
		}
		
		//縦も横も移動していないなら待機に移行
		if (isMoveX == false && isMoveY == false)
		{
			isMove = false;
			mState = EState::EWAIT;
		}
	}
}

//デストラクタ
CEnemy::~CEnemy()
{
	int healPop = rand();
	//3の倍数なら回復を落とす
	if (healPop % 3 == 0)
	{	
		new CHeal(GetX(), mLeg, CHeal::GetTexture());
	}
	//影をタスクリストから削除
	mpShadow->SetEnabled(false);
	mEnemyCount--;
	if (mHp <= 0)
	{
		if (mEnemyType == EEnemyType::Oni)
		{
			CUiFont::GetInstance()->SetScore(ONI_POINT);
		}
		else
		{
			CUiFont::GetInstance()->SetScore(SLIME_POINT);
		}
	}

}

void CEnemy::Attack()
{
	//攻撃コライダの種類
	int attackNumber = 4;

	if (mEnemyType == EEnemyType::Oni)
	{
		attackNumber = 5;
	}

	//攻撃コライダの生成
	CAttack* attack = new CAttack(this, &mX, &mY, &mZ, mVx, attackNumber);
	printf("敵の攻撃コライダ生成\n");
}

void CEnemy::Death()
{
	//タスクリストから削除
	SetEnabled(false);
}

//アニメーションを設定
void CEnemy::SetAnimation()
{
	switch (mState)
	{
	case EState::EWAIT://待機アニメーション
		//右向き
		if (mVx > 0.0f)
		{
			if (mAnimationNum == CAnimationNumber::Move1)     Texture(GetTexture(), TEX_RIGHT1, TEX_WAIT);
			else if (mAnimationNum == CAnimationNumber::Move2)Texture(GetTexture(), TEX_RIGHT2, TEX_WAIT);
			else if (mAnimationNum == CAnimationNumber::Move3)Texture(GetTexture(), TEX_RIGHT3, TEX_WAIT);
			else                                              Texture(GetTexture(), TEX_RIGHT4, TEX_WAIT);
		}
		//左向き
		else
		{
			if (mAnimationNum == CAnimationNumber::Move1)     Texture(GetTexture(), TEX_LEFT1, TEX_WAIT);
			else if (mAnimationNum == CAnimationNumber::Move2)Texture(GetTexture(), TEX_LEFT2, TEX_WAIT);
			else if (mAnimationNum == CAnimationNumber::Move3)Texture(GetTexture(), TEX_LEFT3, TEX_WAIT);
			else                                              Texture(GetTexture(), TEX_LEFT4, TEX_WAIT);
		}
		break;

	case EState::EMOVE://移動アニメーション
		//右移動
		if (mVx > 0.0f)
		{
			if (mAnimationNum == CAnimationNumber::Move1)     Texture(GetTexture(), TEX_RIGHT1, TEX_MOVE);
			else if (mAnimationNum == CAnimationNumber::Move2)Texture(GetTexture(), TEX_RIGHT2, TEX_MOVE);
			else if (mAnimationNum == CAnimationNumber::Move3)Texture(GetTexture(), TEX_RIGHT3, TEX_MOVE);
			else                                              Texture(GetTexture(), TEX_RIGHT4, TEX_MOVE);
		}
		//左移動
		else
		{
			if (mAnimationNum == CAnimationNumber::Move1)     Texture(GetTexture(), TEX_LEFT1, TEX_MOVE);
			else if (mAnimationNum == CAnimationNumber::Move2)Texture(GetTexture(), TEX_LEFT2, TEX_MOVE);
			else if (mAnimationNum == CAnimationNumber::Move3)Texture(GetTexture(), TEX_LEFT3, TEX_MOVE);
			else                                              Texture(GetTexture(), TEX_LEFT4, TEX_MOVE);
		}
		break;

	case EState::EATTACK://攻撃アニメーション
		if (mEnemyType == EEnemyType::Oni)
		{
			if (isAttack == true)
			{
				//右向き
				if (mVx > 0.0f)
				{
					if (mAnimationNum == CAnimationNumber::Move1)     Texture(GetTexture(), TEX_RIGHT1, TEX_ATTACK);
					else if (mAnimationNum == CAnimationNumber::Move2)Texture(GetTexture(), TEX_RIGHT2, TEX_ATTACK);
					else if (mAnimationNum == CAnimationNumber::Move3)Texture(GetTexture(), TEX_RIGHT3, TEX_ATTACK);
					else if (mAnimationNum == CAnimationNumber::Move4)Texture(GetTexture(), TEX_RIGHT4, TEX_ATTACK);
					else if (mAnimationNum == CAnimationNumber::Move5)Texture(GetTexture(), TEX_RIGHT5, TEX_ATTACK);
					else if (mAnimationNum == CAnimationNumber::Move6)Texture(GetTexture(), TEX_RIGHT6, TEX_ATTACK);
					else isAttack = false;
				}
				//左向き
				else
				{
					if (mAnimationNum == CAnimationNumber::Move1)     Texture(GetTexture(), TEX_LEFT1, TEX_ATTACK);
					else if (mAnimationNum == CAnimationNumber::Move2)Texture(GetTexture(), TEX_LEFT2, TEX_ATTACK);
					else if (mAnimationNum == CAnimationNumber::Move3)Texture(GetTexture(), TEX_LEFT3, TEX_ATTACK);
					else if (mAnimationNum == CAnimationNumber::Move4)Texture(GetTexture(), TEX_LEFT4, TEX_ATTACK);
					else if (mAnimationNum == CAnimationNumber::Move5)Texture(GetTexture(), TEX_LEFT5, TEX_ATTACK);
					else if (mAnimationNum == CAnimationNumber::Move6)Texture(GetTexture(), TEX_LEFT6, TEX_ATTACK);
					else isAttack = false;
				}
			}
			break;
		}
		else if (mEnemyType == EEnemyType::Slime)
		{
			if (isAttack == true)
			{
				//右向き
				if (mVx > 0.0f)
				{
					if (mAnimationNum == CAnimationNumber::Move1)     Texture(GetTexture(), TEX_RIGHT1, TEX_ATTACK);
					else if (mAnimationNum == CAnimationNumber::Move2)Texture(GetTexture(), TEX_RIGHT2, TEX_ATTACK);
					else if (mAnimationNum == CAnimationNumber::Move3)Texture(GetTexture(), TEX_RIGHT3, TEX_ATTACK);
					else if (mAnimationNum == CAnimationNumber::Move4)Texture(GetTexture(), TEX_RIGHT4, TEX_ATTACK);
					else isAttack = false;
				}
				//左向き
				else
				{
					if (mAnimationNum == CAnimationNumber::Move1)     Texture(GetTexture(), TEX_LEFT1, TEX_ATTACK);
					else if (mAnimationNum == CAnimationNumber::Move2)Texture(GetTexture(), TEX_LEFT2, TEX_ATTACK);
					else if (mAnimationNum == CAnimationNumber::Move3)Texture(GetTexture(), TEX_LEFT3, TEX_ATTACK);
					else if (mAnimationNum == CAnimationNumber::Move4)Texture(GetTexture(), TEX_LEFT4, TEX_ATTACK);
					else isAttack = false;
				}
			}
			break;
		}
	case EState::EHIT:	//攻撃を受けた時のアニメーション
		if (isHit == true)
		{
			//右向き
			if (mVx > 0.0f)
			{
				if (mAnimationNum == CAnimationNumber::Move1)	      Texture(GetTexture(), TEX_RIGHT1, TEX_HIT);
				else isHit = false;
			}
			else
			{
				if (mAnimationNum == CAnimationNumber::Move1)		  Texture(GetTexture(), TEX_LEFT1, TEX_HIT);
				else isHit = false;
			}
		}
		break;
	}
}

CEnemy::EEnemyType CEnemy::GetEnemyType()
{
	return mEnemyType;
}

//衝突判定
void CEnemy::Collision(CCollider* m, CCollider* o)
{
	float ax, ay;

	switch (o->GetCType())
	{
	case CCollider::EColliderType::EPLAYER:	//プレイヤーの体のコライダとの衝突判定
		//コライダのmとoが衝突しているか判定しているか判定
		if (CCollider::Collision(m, o, &ax, &ay))
		{
			//プレイヤーとの衝突判定を実行(めり込まない処理)
			//SetX(GetX());

			//調整中
			//SetY(GetY());
			//SetZ(GetZ());
			if (CPlayer::GetInstance()->GetState() == EState::EJUMP)
			{
				if (m->GetCType() == CCollider::EColliderType::ESLIME)
				{
					//プレイヤーが落下中なら
					if (mPlayerY >= o->GetmpY())
					{
						mHp -= mHp;
					}
				}
				mPlayerY = o->GetmpY();
			}

			if (isAttack == false)
			{
				if (mVx < 0 && ax > 0 || mVx > 0 && ax < 0)
				{
					if (isHit == false)
					{
						isAttack = true;
						isCollider = true;
					}
				}
			}
		}
		break;
	case CCollider::EColliderType::EPATTACK1:	//プレイヤーの攻撃1のコライダとの衝突判定
		//コライダのmとoが衝突しているか判定しているか判定
		if (CCollider::Collision(m, o, &ax, &ay))
		{
			if (mInvincible == 0)
			{
				//ノックバック処理
				if (ax < 0)
				{
					SetX(GetX() - KNOCKBACK);
				}
				else
				{
					SetX(GetX() + KNOCKBACK);
				}
				mHp -= DAMAGE1 + CPlayer::GetInstance()->GetAttackPower();
				mInvincible = INVINCIBLE;

				std::cout << "攻撃1により敵の残りHPは" << mHp << "です\n";

				isHit = true;
			}
		}
		break;
	case CCollider::EColliderType::EPATTACK2:	//プレイヤーの攻撃2のコライダとの衝突判定
		//コライダのmとoが衝突しているか判定しているか判定
		if (CCollider::Collision(m, o, &ax, &ay))
		{
			if (mInvincible == 0)
			{
				//ノックバック処理
				if (ax < 0)
				{
					SetX(GetX() - KNOCKBACK);
				}
				else
				{
					SetX(GetX() + KNOCKBACK);
				}

				mHp -= DAMAGE2 + CPlayer::GetInstance()->GetAttackPower();
				mInvincible = INVINCIBLE;

				std::cout << "攻撃2により敵の残りHPは" << mHp << "です\n";

				isHit = true;
			}
		}
		break;
	case CCollider::EColliderType::EPATTACK3:	//プレイヤーの攻撃3のコライダとの衝突判定
		//コライダのmとoが衝突しているか判定しているか判定
		if (CCollider::Collision(m, o, &ax, &ay))
		{
			if (mInvincible == 0)
			{
				//ノックバック処理
				if (ax < 0)
				{
					SetX(GetX() - KNOCKBACK);
				}
				else
				{
					SetX(GetX() + KNOCKBACK);
				}
				mHp -= DAMAGE3 + CPlayer::GetInstance()->GetAttackPower();
				mInvincible = INVINCIBLE;

				std::cout << "攻撃3により敵の残りHPは" << mHp << "です\n";

				isHit = true;
			}
		}
		break;
	}

}



