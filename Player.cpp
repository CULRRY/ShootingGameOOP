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
/// @brief Player�� ������ ������Ʈ�Ѵ�.
///	@detail Player�� ������ ���� Ű�Է¿��� ó���ǹǷ� ������ī��Ʈ�� �ø�
//-----------------------------------------------------------------------------
bool Player::Update()
{
	_frameCount++;
	return true;
}

//-----------------------------------------------------------------------------
/// @brief Enemy�� ScreenBuffer�� ����Ѵ�.
//-----------------------------------------------------------------------------
void Player::Render()
{
	ScreenBuffer::Instance()->DrawSprite(_y, _x, '#');
}

//-----------------------------------------------------------------------------
/// @brief Player�� �Ѿ��� �߻��Ѵ�.
//-----------------------------------------------------------------------------
void Player::Attack()
{
	ObjectManager::Instance()->CreateObject(new BulletPlayer(_y - 1, _x, BulletDirection::CENTER, _bulletSpeed));
}

//-----------------------------------------------------------------------------
/// @brief �̵��ӵ� ����� ���� ���� �����ӿ� ������ �� �ִ��� �Ǵ��Ѵ�.
//-----------------------------------------------------------------------------
bool Player::CanMoveCurrentFrame()
{
	return _frameCount % _moveSpeed == 0;
}

//-----------------------------------------------------------------------------
/// @brief ���ݼӵ� ����� ���� ���� �����ӿ� ������ �� �ִ��� �Ǵ��Ѵ�.
//-----------------------------------------------------------------------------
bool Player::CanAttackCurrentFrame()
{
	return _frameCount % _attackFrequency == 0;
}

//-----------------------------------------------------------------------------
/// @brief �浹�� �Ͼ���� �Ǵ��Ѵ�.
///
/// @param other �浹�� �Ͼ Object
///	@return BULLET_ENEMY�� ����� ���� true
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
/// @brief �浹���� ���� ������ ó���Ѵ�.
/// @param other �浹�� ��ü
//-----------------------------------------------------------------------------
void Player::OnCollision(BaseObject* other)
{

	_hp--;
}

//-----------------------------------------------------------------------------
/// @brief Player�� ��ġ�� �����ǥ�� �����Ѵ�.
///
/// @param dy �̵� y�� ��ȭ��
/// @param dx �̵� x�� ��ȭ��
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
/// @brief Player�� �������θ� �Ǵ��Ѵ�.
///
/// @return Player ��������
//-----------------------------------------------------------------------------
bool Player::IsSurvive()
{
	if (_hp <= 0)
	{
		return false;
	}

	return true;
}
