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
/// @brief �Ѿ��� ������ ó���Ѵ�.
///
/// @return ������ �����̶�� false, �ƴϸ� true
//-----------------------------------------------------------------------------
bool BulletEnemy::Update()
{
	_frameCount++;
	return move();
}

//-----------------------------------------------------------------------------
/// @brief �Ѿ��� ScreenBuffer�� ����Ѵ�
//-----------------------------------------------------------------------------
void BulletEnemy::Render()
{
	ScreenBuffer::Instance()->DrawSprite(_y, _x, '*');
}

//-----------------------------------------------------------------------------
/// @brief �浹�� �Ͼ�� ���� ������ ó���Ѵ�.
///
/// @param other �浹�� �Ͼ Object
//-----------------------------------------------------------------------------
void BulletEnemy::OnCollision(BaseObject* other)
{
	// �浹����� Player�϶���
	if (other->GetObjectType() == ObjectType::PLAYER)
	{
		ReserveDelete();
	}
}

//-----------------------------------------------------------------------------
/// @brief �Ѿ��� ��ǥ�� �����Ų��.
///
/// @return �̵���Ų ��ǥ�� ���� IsBound()�� �����.
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

