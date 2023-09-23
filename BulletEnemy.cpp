#include "stdafx.h"
#include "BulletEnemy.h"
#include "ScreenBuffer.h"
#include "ObjectType.h"

BulletEnemy::BulletEnemy(int32 y, int32 x, BulletDirection dir, int32 speed)
	: Bullet(y, x, ObjectType::BULLET_ENEMY, dir, speed)
{
}

BulletEnemy::~BulletEnemy()
{
}

//-----------------------------------------------------------------------------
/// @brief 총알의 로직을 처리한다.
///
/// @return 삭제될 예정이라면 false, 아니면 true
//-----------------------------------------------------------------------------
bool BulletEnemy::Update()
{
	_frameCount++;
	return move();
}

//-----------------------------------------------------------------------------
/// @brief 총알은 ScreenBuffer에 출력한다
//-----------------------------------------------------------------------------
void BulletEnemy::Render()
{
	ScreenBuffer::Instance()->DrawSprite(_y, _x, '*');
}

//-----------------------------------------------------------------------------
/// @brief 충돌이 일어났을 때의 로직을 처리한다.
///
/// @param other 충돌이 일어난 Object
//-----------------------------------------------------------------------------
void BulletEnemy::OnCollision(BaseObject* other)
{
	// 충돌대상이 Player일때만
	if (other->GetObjectType() == ObjectType::PLAYER)
	{
		ReserveDelete();
	}
}

//-----------------------------------------------------------------------------
/// @brief 총알의 좌표를 변경시킨다.
///
/// @return 이동시킨 좌표에 대해 IsBound()의 결과값.
//-----------------------------------------------------------------------------
bool BulletEnemy::move()
{
	if (CanMoveCurrentFrame())
	{
		_x += DELTA_X[(int32)_direction];
		_y += 1;

		if (IsBound() == false)
		{
			return false;
		}
	}

	return true;
}

