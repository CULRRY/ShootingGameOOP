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
/// @brief �Ѿ��� ������ ó���Ѵ�.
///
/// @return ������ �����̶�� false, �ƴϸ� true
//-----------------------------------------------------------------------------
bool BulletPlayer::Update()
{
	_frameCount++;
	return move();
}

//-----------------------------------------------------------------------------
/// @brief �Ѿ��� ScreenBuffer�� ����Ѵ�
//-----------------------------------------------------------------------------
void BulletPlayer::Render()
{
	ScreenBuffer::Instance()->DrawSprite(_y, _x, '^');
}

//-----------------------------------------------------------------------------
/// @brief �浹�� �Ͼ�� ���� ������ ó���Ѵ�.
///
/// @param other �浹�� �Ͼ Object
//-----------------------------------------------------------------------------
void BulletPlayer::OnCollision(BaseObject* other)
{
	// �浹����� Enemy�϶���
	if (other->GetObjectType() == ObjectType::ENEMY)
	{
		ReserveDelete();
	}
}

//-----------------------------------------------------------------------------
/// @brief �Ѿ��� ��ǥ�� �����Ų��.
///
/// @return �̵���Ų ��ǥ�� ���� IsBound()�� �����.
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
