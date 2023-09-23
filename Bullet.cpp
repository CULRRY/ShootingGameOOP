#include "stdafx.h"
#include "Bullet.h"
#include "ScreenBuffer.h"

Bullet::Bullet(int32 y, int32 x, ObjectType type, BulletDirection dir, int32 speed)
	:BaseObject(y, x, type), _direction(dir), _speed(speed)
{
}


//-----------------------------------------------------------------------------
/// @brief 총알이 버퍼 바깥으로 나갔는지 판단한다.
///
/// @return 나갔으면 false, 아니면 true
//-----------------------------------------------------------------------------
bool Bullet::IsBound() const
{
	if (_x < 0 || _x >= ScreenBuffer::SCREEN_WIDTH || _y < 0 || _y >= ScreenBuffer::SCREEN_HEIGHT)
	{
		return false;
	}

	return true;
}

//-----------------------------------------------------------------------------
/// @brief 총알의 이동속도를 처리하기위해 해당 프레임에 움직일 수 있는지 판단한다.
///
/// @return 할수 있으면 true, 아니면 false.
//-----------------------------------------------------------------------------
bool Bullet::CanMoveCurrentFrame() const
{
	return _frameCount % _speed == 0;;
}
