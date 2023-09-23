#pragma once
#include "BaseObject.h"

/// @brief 총알을 발사하는 뱡향
enum class BulletDirection
{
	LEFT,
	CENTER,
	RIGHT,
};

class Bullet : public BaseObject
{

public:
	Bullet(int32 y, int32 x, ObjectType type, BulletDirection dir, int32 speed);

	virtual bool move() = 0; ///< 총알이 움직이는 로직을 처리한다.

protected:
	bool IsBound() const;
	bool CanMoveCurrentFrame() const;

protected:
	int32				_speed;		///< 총알 이동속도
	BulletDirection		_direction; ///< 총알의 방향
};

