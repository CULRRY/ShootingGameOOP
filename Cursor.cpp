#include "stdafx.h"
#include "Cursor.h"
#include "ScreenBuffer.h"
#include "ObjectType.h"

Cursor::Cursor(int32 y, int32 x, int32 minY, int32 minX, int32 maxY, int32 maxX)
	: BaseObject(y, x, ObjectType::CURSOR), _maxY(maxY), _minY(minY), _maxX(maxX), _minX(minX)
{
}

Cursor::~Cursor()
{
}

bool Cursor::Update()
{
	return true;
}

//-----------------------------------------------------------------------------
/// @brief Ŀ���� ScreenBuffer�� ����Ѵ�
//-----------------------------------------------------------------------------
void Cursor::Render()
{
	ScreenBuffer::Instance()->DrawSprite(_y, _x, '>');
}

//-----------------------------------------------------------------------------
/// @brief Ŀ���� �̵���Ų��.
///
/// @param dy �̵� y�� ��ȭ��
/// @param dx �̵� x�� ��ȭ��
//-----------------------------------------------------------------------------
void Cursor::Move(int32 dy, int32 dx)
{
	_y = _y + dy;
	_x = _x + dx;
	_y = max(_y, _minY);
	_y = min(_y, _maxY);
	_x = max(_x, _minX);
	_x = min(_x, _maxX);
}

//-----------------------------------------------------------------------------
/// @brief ���� ���õǾ��ִ� TextBox�� ��ȯ�Ѵ�.
///
/// @return ���� ���õǾ��ִ� TextBox ������
//-----------------------------------------------------------------------------
BaseObject* Cursor::SelectMenu()
{
	return _currentSelectedMenu;
}

//-----------------------------------------------------------------------------
/// @brief �ٸ� Object�� ���� y��ǥ�� �����ϸ� �浹�� �����Ѵ�.
///
/// @param other �浹�� Object
/// @return �浹 ����
//-----------------------------------------------------------------------------
bool Cursor::IsCollision(BaseObject* other)
{
	// �浹�� ��ü�� TEXT_BOX�϶���
	if (other->GetObjectType() == ObjectType::TEXT_BOX)
	{
		return other->IsSameHeight(_y);
	}

	return false;
}

//-----------------------------------------------------------------------------
/// @brief �浹�ߴٸ� ���� ���õ� TextBox�� �ش� ��ü�� �ٲ۴�.
/// @param other �浹�� ��ü
//-----------------------------------------------------------------------------
void Cursor::OnCollision(BaseObject* other)
{
	_currentSelectedMenu = other;
}
