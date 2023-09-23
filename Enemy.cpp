#include "stdafx.h"
#include "Enemy.h"

#include "Bullet.h"
#include "BulletEnemy.h"
#include "EnemyInfo.h"
#include "MovementInfo.h"
#include "ObjectType.h"
#include "ScreenBuffer.h"
#include "DataLoader.h"
#include "ObjectManager.h"

Enemy::Enemy(int32 y, int32 x, int32 id) : BaseObject(y, x, ObjectType::ENEMY), _movementCount(0)
{
	// id�� ���� info ����
	_info = DataLoader::Instance()->GetEnemyInfo(id);
	_hp = _info->hp;
}

Enemy::~Enemy()
{
}


//-----------------------------------------------------------------------------
/// @brief Enemy�� ������ ������Ʈ�Ѵ�. (����, �̵�)
//-----------------------------------------------------------------------------
bool Enemy::Update()
{
	_frameCount++;
	if (CanMoveCurrentFrame() == true)
	{
		Move(_info->movement.dy[_movementCount % _info->movement.size], _info->movement.dx[_movementCount % _info->movement.size]);
		_movementCount++;
	}

	Attack();

	return true;
}

//-----------------------------------------------------------------------------
/// @brief Enemy�� ScreenBuffer�� ����Ѵ�.
//-----------------------------------------------------------------------------
void Enemy::Render()
{
	for (int32 y = _y - 1; y <= _y + 1; y++)
	{
		for (int32 x = _x - 2; x <= _x + 2; x++)
		{
			if (y < 0 || y >= ScreenBuffer::SCREEN_HEIGHT || x < 0 || x >= ScreenBuffer::SCREEN_WIDTH)
			{
				continue;
			}

			const char dot = _info->graphic[y - (_y - 1)][x - (_x - 2)];

			if (dot == '-')
			{
				continue;
			}
			ScreenBuffer::Instance()->DrawSprite(y, x, dot);
		}
	}
}

//-----------------------------------------------------------------------------
/// @brief �浹�� �Ͼ���� �Ǵ��Ѵ�.
///
/// @param other �浹�� �Ͼ Object
///	@return BULLET_PLAYER�� ����� ���� true
//-----------------------------------------------------------------------------
bool Enemy::IsCollision(BaseObject* other)
{
	if (other->GetObjectType() == ObjectType::BULLET_PLAYER)
	{
		for (int32 y = _y - 1; y <= _y + 1; y++)
		{
			for (int32 x = _x - 2; x <= _x + 2; x++)
			{
				if (y < 0 || y >= ScreenBuffer::SCREEN_HEIGHT || x < 0 || x >= ScreenBuffer::SCREEN_WIDTH)
				{
					continue;
				}

				const char dot = _info->graphic[y - _y - 1][x - _x - 2];

				if (dot == '-')
				{
					continue;
				}

				if (other->IsSamePosition(y, x) == true)
					return true;
			}
		}
	}

	return false;
}

//-----------------------------------------------------------------------------
/// @brief �浹���� ���� ������ ó���Ѵ�.
/// @param other �浹�� ��ü
//-----------------------------------------------------------------------------
void Enemy::OnCollision(BaseObject* other)
{
	_hp--;
	if (_hp <= 0)
	{
		ReserveDelete();
	}
}


//-----------------------------------------------------------------------------
/// @brief Enemy�� ��ġ�� �����ǥ�� �����Ѵ�.
///
/// @param dy �̵� y�� ��ȭ��
/// @param dx �̵� x�� ��ȭ��
//-----------------------------------------------------------------------------
void Enemy::Move(int dy, int dx)
{
	_y = _y + dy;
	_x = _x + dx;
	_y = max(_y, 0);
	_y = min(_y, ScreenBuffer::SCREEN_HEIGHT - 1);
	_x = max(_x, 0);
	_x = min(_x, ScreenBuffer::SCREEN_WIDTH - 2);
}

//-----------------------------------------------------------------------------
/// @brief Enemy�� �Ѿ��� �߻��Ѵ�.
//-----------------------------------------------------------------------------
void Enemy::Attack()
{
	if (CanAttackCurrentFrame() == true)
	{
		for (int32 bulletIdx = 0; bulletIdx < _info->BulletCount; bulletIdx++)
		{
			ObjectManager::Instance()->CreateObject(new BulletEnemy(
				_y + 2,
				_x + _info->BulletXPosition[bulletIdx],
				(BulletDirection)_info->BulletDirection[bulletIdx],
				_info->bulletSpeed)
			);
		}
	}
}

//-----------------------------------------------------------------------------
/// @brief �̵��ӵ� ����� ���� ���� �����ӿ� ������ �� �ִ��� �Ǵ��Ѵ�.
//-----------------------------------------------------------------------------
bool Enemy::CanMoveCurrentFrame() const
{
	return _frameCount % _info->moveSpeed == 0;
}

//-----------------------------------------------------------------------------
/// @brief ���ݼӵ� ����� ���� ���� �����ӿ� ������ �� �ִ��� �Ǵ��Ѵ�.
//-----------------------------------------------------------------------------
bool Enemy::CanAttackCurrentFrame() const
{
	return _frameCount % _info->attackFrequency == 0;
}