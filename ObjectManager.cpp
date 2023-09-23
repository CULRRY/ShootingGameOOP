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
/// @brief Object�� �����Ѵ�.
///
/// @param obj ������ object�� ������
//-----------------------------------------------------------------------------
void ObjectManager::CreateObject(BaseObject* obj)
{
	_objectList.push_back(obj);
}


//-----------------------------------------------------------------------------
/// @brief ObjectList�� ����. Scene��ȯ�� ���.
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
/// @brief	�Ķ���ͷ� �־��� ObjectType�� ����
///			���� ����Ʈ�� �� ��� �ش� Type ��ü�� ����ִ��� ��ȯ�Ѵ�.
///
/// @param type ������ ������ϴ� ObjectType
/// @return ���� ����Ʈ�� ����ִ� �ش� type�� ��ü�� ����
//-----------------------------------------------------------------------------
int32 ObjectManager::GetCountByObjectType(ObjectType type)
{
	return _objectCount[(int32)type];
}

//-----------------------------------------------------------------------------
/// @brief ���� �����ϰ� �ִ� Object���� ������ �ϰ������� ó���Ѵ�.
//-----------------------------------------------------------------------------
void ObjectManager::Update()
{
	// Object�� Ÿ�Ժ� ������ ������� �迭�� �������Ӹ��� �ʱ�ȭ
	::memset(_objectCount, 0, sizeof(uint32) * (uint32)ObjectType::OBJECT_TYPE_COUNT);
	for (List<BaseObject*>::iterator it = _objectList.begin(); it != _objectList.end(); ++it)
	{
		BaseObject* object = *it;

		// ī��Ʈ ����
		_objectCount[(int32)object->GetObjectType()]++;

		// ���� ������Ʈ
		if(object->Update() == false)
		{
			object->ReserveDelete();
		}

		// �浹 ó��
		for (BaseObject* target : _objectList)
		{
			if (object->IsCollision(target))
			{
				object->OnCollision(target);
				target->OnCollision(object);
			}
		}
	}

	// ����� ������ ��ü�� �ϰ� ����.
	DeleteObjects();

}

//-----------------------------------------------------------------------------
/// @brief ���� �����ϰ��ִ� ��� Object�� ȭ�鿡 ����Ѵ�.
//-----------------------------------------------------------------------------
void ObjectManager::Render()
{
	// ���� ����
	ScreenBuffer::Instance()->Clear();
	// ���ۿ� ���
	for (BaseObject* object : _objectList)
	{
		object->Render();
	}
	// ���
	ScreenBuffer::Instance()->Flip();
}

//-----------------------------------------------------------------------------
/// @brief ���� ������ ���� ������������ ��ϵ� ��ü���� ���������� �����Ѵ�.
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
