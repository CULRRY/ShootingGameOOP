#pragma once
#include "List.h"
#include "ObjectType.h"

class BaseObject;

class ObjectManager
{
	using DeleteObjectIterator = List<BaseObject*>::iterator;

public:
	void	CreateObject(BaseObject* obj);
	void	ClearObject();
	void	Update();
	void	Render();

	int32	GetCountByObjectType(ObjectType type);

private:
	void	DeleteObjects();
private:
	List<BaseObject*>		_objectList;
	uint32					_objectCount[(int32)ObjectType::OBJECT_TYPE_COUNT];

//----------------------------------------------------------------------------
// Singleton
//----------------------------------------------------------------------------
private:
	ObjectManager();
	~ObjectManager();
public:
	static ObjectManager* Instance()
	{
		if (_instance == nullptr)
		{
			_instance = new ObjectManager();
			::atexit(Destroy);
		}

		return _instance;
	}

	static void Destroy()
	{
		delete _instance;
		_instance = nullptr;
	}
private:
	inline static ObjectManager* _instance = nullptr;
};

