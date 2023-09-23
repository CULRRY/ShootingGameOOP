#pragma once

enum class ObjectType
{
	PLAYER,
	ENEMY,
	BULLET_ENEMY,
	BULLET_PLAYER,
	CURSOR,
	TEXT_BOX,



	OBJECT_TYPE_COUNT, ///< Type의 총 갯수를 알기위해 마지막 Enum에 배치
};