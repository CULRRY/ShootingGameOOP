#pragma once

enum class ObjectType;

class BaseObject
{
public:
	BaseObject(int32 y, int32 x, ObjectType type)
		: _y(y), _x(x), _frameCount(0), _objectType(type)
	{};
	virtual ~BaseObject() {};

	/// @brief Object�� ������ ������Ʈ�Ѵ�.
	virtual bool Update() = 0;

	/// @brief Object�� ScreenBuffer�� �������Ѵ�.
	virtual void Render() = 0;
	
	/// @brief �浹�� �Ͼ�� �� �ϴ� �ൿ�� �����Ѵ�.
	virtual void OnCollision(BaseObject* other) = 0;

	/// @brief �浹�� �Ǵ��Ѵ�. �浹�� ���� ��ü�� overriding �����������.
	virtual bool IsCollision(BaseObject* other) 
	{
		return false;
	}

	/// @brief �ش� Object�� Update ������ ������ �����ǵ��� �����Ѵ�.
	void ReserveDelete()
	{
		_isAvailable = true;
	}

	/// @brief ���� ������ ����, �ش� Object�� ������������ �Ǵ��Ѵ�.
	bool IsDeleted() const
	{
		return _isAvailable;
	}

	/// @brief Object�� y, x��ǥ�� �ִ��� Ȯ���Ѵ�.
	bool IsSamePosition(int32 y, int32 x) const
	{
		return _y == y && _x == x;
	}

	/// @brief Object�� y��ǥ�� �ִ��� Ȯ���Ѵ�. Ŀ���� �޴��� �����ϱ� ���� ���� ���. 
	bool IsSameHeight(int32 y) const
	{
		return _y == y;
	}

	/// @brief Object�� Type�� Ȯ���Ѵ�.
	ObjectType GetObjectType() const { return _objectType; }


protected:
	int32		_y;						///< y��ǥ
	int32		_x;						///< x��ǥ
	uint64		_frameCount;			///< �̵�, ���ݼӵ� ����� ���� frame ī��Ʈ
	ObjectType	_objectType;			///< ObjectType
	bool		_isAvailable = false;	///< Object�� ������������ �Ǵ��ϴ� boolean
};