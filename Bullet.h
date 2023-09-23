#pragma once
#include "BaseObject.h"

/// @brief �Ѿ��� �߻��ϴ� ����
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

	virtual bool move() = 0; ///< �Ѿ��� �����̴� ������ ó���Ѵ�.

protected:
	bool IsBound() const;
	bool CanMoveCurrentFrame() const;

protected:
	int32				_speed;		///< �Ѿ� �̵��ӵ�
	BulletDirection		_direction; ///< �Ѿ��� ����
};

