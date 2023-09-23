#include "stdafx.h"
#include "Player.h"

#include "ObjectType.h"
#include "ScreenBuffer.h"
#include "ObjectManager.h"
#include "BulletPlayer.h"

Player::Player() : BaseObject(19, 32, ObjectType::PLAYER)
{
	_maxHp = 10;
	_hp = _maxHp;
	_moveSpeed = 3;
	_attackFrequency = 6;
	_bulletSpeed = 3;
}

Player::~Player()
{
}

//-----------------------------------------------------------------------------
/// @brief Player의 로직을 업데이트한다.
///	@detail Player의 로직은 보통 키입력에서 처리되므로 프레임카운트만 올림
//-----------------------------------------------------------------------------
bool Player::Update()
{
	_frameCount++;
	return true;
}

//-----------------------------------------------------------------------------
/// @brief Enemy를 ScreenBuffer에 출력한다.
//-----------------------------------------------------------------------------
void Player::Render()
{
	ScreenBuffer::Instance()->DrawSprite(_y, _x, '#');
}

//-----------------------------------------------------------------------------
/// @brief Player가 총알을 발사한다.
//-----------------------------------------------------------------------------
void Player::Attack()
{
	ObjectManager::Instance()->CreateObject(new BulletPlayer(_y - 1, _x, BulletDirection::CENTER, _bulletSpeed));
}

//-----------------------------------------------------------------------------
/// @brief 이동속도 계산을 위해 현재 프레임에 움직일 수 있는지 판단한다.
//-----------------------------------------------------------------------------
bool Player::CanMoveCurrentFrame()
{
	return _frameCount % _moveSpeed == 0;
}

//-----------------------------------------------------------------------------
/// @brief 공격속도 계산을 위해 현재 프레임에 공격할 수 있는지 판단한다.
//-----------------------------------------------------------------------------
bool Player::CanAttackCurrentFrame()
{
	return _frameCount % _attackFrequency == 0;
}

//-----------------------------------------------------------------------------
/// @brief 충돌이 일어났는지 판단한다.
///
/// @param other 충돌이 일어난 Object
///	@return BULLET_ENEMY와 닿았을 때만 true
//-----------------------------------------------------------------------------
bool Player::IsCollision(BaseObject* other)
{
	if (other->GetObjectType() == ObjectType::BULLET_ENEMY)
	{
		return other->IsSamePosition(_y, _x);
	}

	return false;
}

//-----------------------------------------------------------------------------
/// @brief 충돌했을 때의 로직을 처리한다.
/// @param other 충돌한 객체
//-----------------------------------------------------------------------------
void Player::OnCollision(BaseObject* other)
{

	_hp--;
}

//-----------------------------------------------------------------------------
/// @brief Player의 위치를 상대좌표로 변경한다.
///
/// @param dy 이동 y값 변화량
/// @param dx 이동 x값 변화량
//-----------------------------------------------------------------------------
void Player::Move(int dy, int dx)
{
	_y = _y + dy;
	_x = _x + dx;
	_y = max(_y, 0);
	_y = min(_y, ScreenBuffer::SCREEN_HEIGHT - 1);
	_x = max(_x, 0);
	_x = min(_x, ScreenBuffer::SCREEN_WIDTH - 2);
}

//-----------------------------------------------------------------------------
/// @brief Player의 생존여부를 판단한다.
///
/// @return Player 생존여부
//-----------------------------------------------------------------------------
bool Player::IsSurvive()
{
	if (_hp <= 0)
	{
		return false;
	}

	return true;
}
