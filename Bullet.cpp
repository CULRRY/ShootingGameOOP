#include "stdafx.h"
#include "Bullet.h"
#include "ScreenBuffer.h"

Bullet::Bullet(int32 y, int32 x, ObjectType type, BulletDirection dir, int32 speed)
	:BaseObject(y, x, type), _direction(dir), _speed(speed)
{
}


//-----------------------------------------------------------------------------
/// @brief �Ѿ��� ���� �ٱ����� �������� �Ǵ��Ѵ�.
///
/// @return �������� false, �ƴϸ� true
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
/// @brief �Ѿ��� �̵��ӵ��� ó���ϱ����� �ش� �����ӿ� ������ �� �ִ��� �Ǵ��Ѵ�.
///
/// @return �Ҽ� ������ true, �ƴϸ� false.
//-----------------------------------------------------------------------------
bool Bullet::CanMoveCurrentFrame() const
{
	return _frameCount % _speed == 0;;
}
