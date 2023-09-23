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
	// id를 통해 info 얻어옴
	_info = DataLoader::Instance()->GetEnemyInfo(id);
	_hp = _info->hp;
}

Enemy::~Enemy()
{
}


//-----------------------------------------------------------------------------
/// @brief Enemy의 로직을 업데이트한다. (공격, 이동)
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
/// @brief Enemy를 ScreenBuffer에 출력한다.
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
/// @brief 충돌이 일어났는지 판단한다.
///
/// @param other 충돌이 일어난 Object
///	@return BULLET_PLAYER와 닿았을 때만 true
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
/// @brief 충돌했을 때의 로직을 처리한다.
/// @param other 충돌한 객체
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
/// @brief Enemy의 위치를 상대좌표로 변경한다.
///
/// @param dy 이동 y값 변화량
/// @param dx 이동 x값 변화량
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
/// @brief Enemy가 총알을 발사한다.
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
/// @brief 이동속도 계산을 위해 현재 프레임에 움직일 수 있는지 판단한다.
//-----------------------------------------------------------------------------
bool Enemy::CanMoveCurrentFrame() const
{
	return _frameCount % _info->moveSpeed == 0;
}

//-----------------------------------------------------------------------------
/// @brief 공격속도 계산을 위해 현재 프레임에 공격할 수 있는지 판단한다.
//-----------------------------------------------------------------------------
bool Enemy::CanAttackCurrentFrame() const
{
	return _frameCount % _info->attackFrequency == 0;
}