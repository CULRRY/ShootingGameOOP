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
/// @brief 커서를 ScreenBuffer에 출력한다
//-----------------------------------------------------------------------------
void Cursor::Render()
{
	ScreenBuffer::Instance()->DrawSprite(_y, _x, '>');
}

//-----------------------------------------------------------------------------
/// @brief 커서를 이동시킨다.
///
/// @param dy 이동 y값 변화량
/// @param dx 이동 x값 변화량
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
/// @brief 현재 선택되어있는 TextBox를 반환한다.
///
/// @return 현재 선택되어있는 TextBox 포인터
//-----------------------------------------------------------------------------
BaseObject* Cursor::SelectMenu()
{
	return _currentSelectedMenu;
}

//-----------------------------------------------------------------------------
/// @brief 다른 Object와 같은 y좌표상에 존재하면 충돌로 간주한다.
///
/// @param other 충돌한 Object
/// @return 충돌 여부
//-----------------------------------------------------------------------------
bool Cursor::IsCollision(BaseObject* other)
{
	// 충돌한 객체가 TEXT_BOX일때만
	if (other->GetObjectType() == ObjectType::TEXT_BOX)
	{
		return other->IsSameHeight(_y);
	}

	return false;
}

//-----------------------------------------------------------------------------
/// @brief 충돌했다면 현재 선택된 TextBox를 해당 객체로 바꾼다.
/// @param other 충돌한 객체
//-----------------------------------------------------------------------------
void Cursor::OnCollision(BaseObject* other)
{
	_currentSelectedMenu = other;
}
