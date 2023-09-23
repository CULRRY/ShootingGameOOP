#pragma once

enum class ObjectType;

class BaseObject
{
public:
	BaseObject(int32 y, int32 x, ObjectType type)
		: _y(y), _x(x), _frameCount(0), _objectType(type)
	{};
	virtual ~BaseObject() {};

	/// @brief Object의 로직을 업데이트한다.
	virtual bool Update() = 0;

	/// @brief Object를 ScreenBuffer에 렌더링한다.
	virtual void Render() = 0;
	
	/// @brief 충돌이 일어났을 떄 하는 행동을 정의한다.
	virtual void OnCollision(BaseObject* other) = 0;

	/// @brief 충돌을 판단한다. 충돌이 없는 객체는 overriding 하지않으면됨.
	virtual bool IsCollision(BaseObject* other) 
	{
		return false;
	}

	/// @brief 해당 Object가 Update 로직이 끝나고 삭제되도록 예약한다.
	void ReserveDelete()
	{
		_isAvailable = true;
	}

	/// @brief 지연 삭제를 위해, 해당 Object가 삭제예정인지 판단한다.
	bool IsDeleted() const
	{
		return _isAvailable;
	}

	/// @brief Object가 y, x좌표에 있는지 확인한다.
	bool IsSamePosition(int32 y, int32 x) const
	{
		return _y == y && _x == x;
	}

	/// @brief Object가 y좌표에 있는지 확인한다. 커서가 메뉴를 선택하기 위해 만든 기능. 
	bool IsSameHeight(int32 y) const
	{
		return _y == y;
	}

	/// @brief Object의 Type을 확인한다.
	ObjectType GetObjectType() const { return _objectType; }


protected:
	int32		_y;						///< y좌표
	int32		_x;						///< x좌표
	uint64		_frameCount;			///< 이동, 공격속도 계산을 위한 frame 카운트
	ObjectType	_objectType;			///< ObjectType
	bool		_isAvailable = false;	///< Object가 삭제예정인지 판단하는 boolean
};