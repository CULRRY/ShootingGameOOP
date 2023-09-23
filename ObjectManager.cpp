#include "stdafx.h"
#include "ObjectManager.h"
#include "BaseObject.h"
#include "ScreenBuffer.h"

ObjectManager::ObjectManager() : _objectList(List<BaseObject*>()), _objectCount{{0, }}
{
}

ObjectManager::~ObjectManager()
{
}

//-----------------------------------------------------------------------------
/// @brief Object를 생성한다.
///
/// @param obj 생성할 object의 포인터
//-----------------------------------------------------------------------------
void ObjectManager::CreateObject(BaseObject* obj)
{
	_objectList.push_back(obj);
}


//-----------------------------------------------------------------------------
/// @brief ObjectList를 비운다. Scene전환에 사용.
//-----------------------------------------------------------------------------
void ObjectManager::ClearObject()
{
	for (BaseObject* obj : _objectList)
	{
		delete obj;
	}

	_objectList.clear();
}

//-----------------------------------------------------------------------------
/// @brief	파라미터로 넣어준 ObjectType에 대해
///			현재 리스트의 총 몇개의 해당 Type 객체가 들어있는지 반환한다.
///
/// @param type 갯수를 얻고자하는 ObjectType
/// @return 현재 리스트의 들어있는 해당 type인 객체의 갯수
//-----------------------------------------------------------------------------
int32 ObjectManager::GetCountByObjectType(ObjectType type)
{
	return _objectCount[(int32)type];
}

//-----------------------------------------------------------------------------
/// @brief 현재 관리하고 있는 Object들의 로직을 일괄적으로 처리한다.
//-----------------------------------------------------------------------------
void ObjectManager::Update()
{
	// Object의 타입별 갯수를 얻기위해 배열을 매프레임마다 초기화
	::memset(_objectCount, 0, sizeof(uint32) * (uint32)ObjectType::OBJECT_TYPE_COUNT);
	for (List<BaseObject*>::iterator it = _objectList.begin(); it != _objectList.end(); ++it)
	{
		BaseObject* object = *it;

		// 카운트 증가
		_objectCount[(int32)object->GetObjectType()]++;

		// 로직 업데이트
		if(object->Update() == false)
		{
			object->ReserveDelete();
		}

		// 충돌 처리
		for (BaseObject* target : _objectList)
		{
			if (object->IsCollision(target))
			{
				object->OnCollision(target);
				target->OnCollision(object);
			}
		}
	}

	// 예약된 삭제할 객체들 일괄 삭제.
	DeleteObjects();

}

//-----------------------------------------------------------------------------
/// @brief 현재 관리하고있는 모든 Object를 화면에 출력한다.
//-----------------------------------------------------------------------------
void ObjectManager::Render()
{
	// 버퍼 비우기
	ScreenBuffer::Instance()->Clear();
	// 버퍼에 등록
	for (BaseObject* object : _objectList)
	{
		object->Render();
	}
	// 출력
	ScreenBuffer::Instance()->Flip();
}

//-----------------------------------------------------------------------------
/// @brief 지연 삭제를 위해 삭제예정으로 등록된 객체들을 실질적으로 삭제한다.
//-----------------------------------------------------------------------------
void ObjectManager::DeleteObjects()
{
	for (List<BaseObject*>::iterator it = _objectList.begin(); it != _objectList.end();)
	{
		BaseObject* deletedObj = *it;

		if (deletedObj->IsDeleted())
		{
			delete deletedObj;
			it = _objectList.erase(it);
		}
		else
		{
			++it;
		}
	}
}
