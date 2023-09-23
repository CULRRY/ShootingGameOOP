#include "stdafx.h"
#include "BulletPlayer.h"

#include "ObjectManager.h"
#include "ScreenBuffer.h"
#include "ObjectType.h"

BulletPlayer::BulletPlayer(int32 y, int32 x, BulletDirection dir, int32 speed)
	: Bullet(y, x, ObjectType::BULLET_PLAYER, dir, speed)
{
}

BulletPlayer::~BulletPlayer()
{
}

//-----------------------------------------------------------------------------
/// @brief 총알의 로직을 처리한다.
///
/// @return 삭제될 예정이라면 false, 아니면 true
//-----------------------------------------------------------------------------
bool BulletPlayer::Update()
{
	_frameCount++;
	return move();
}

//-----------------------------------------------------------------------------
/// @brief 총알을 ScreenBuffer에 출력한다
//-----------------------------------------------------------------------------
void BulletPlayer::Render()
{
	ScreenBuffer::Instance()->DrawSprite(_y, _x, '^');
}

//-----------------------------------------------------------------------------
/// @brief 충돌이 일어났을 때의 로직을 처리한다.
///
/// @param other 충돌이 일어난 Object
//-----------------------------------------------------------------------------
void BulletPlayer::OnCollision(BaseObject* other)
{
	// 충돌대상이 Enemy일때만
	if (other->GetObjectType() == ObjectType::ENEMY)
	{
		ReserveDelete();
	}
}

//-----------------------------------------------------------------------------
/// @brief 총알의 좌표를 변경시킨다.
///
/// @return 이동시킨 좌표에 대해 IsBound()의 결과값.
//-----------------------------------------------------------------------------
bool BulletPlayer::move()
{
	if (CanMoveCurrentFrame())
	{
		_y += -1;

		if (IsBound() == false)
		{
			return false;
		}
	}

	return true;
}
