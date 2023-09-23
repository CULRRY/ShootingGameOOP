#pragma once
#include "BaseObject.h"

class Cursor : public BaseObject
{
public:
	Cursor(int32 y, int32 x, int32 minY, int32 minX, int32 maxY, int32 maxX);
	~Cursor() override;

	bool			Update() override;
	void			Render() override;
	bool			IsCollision(BaseObject* other) override;
	void			OnCollision(BaseObject* other) override;

	void			Move(int32 dy, int32 dx);
	BaseObject*		SelectMenu();

private:
	int32			_maxY;							///< 커서가 이동가능한 최대 Y좌표
	int32			_minY;							///< 커서가 이동가능한 최소 Y좌표
	int32			_maxX;							///< 커서가 이동가능한 최대 X좌표
	int32			_minX;							///< 커서가 이동가능한 최소 X좌표
	BaseObject*		_currentSelectedMenu = nullptr;	///< 현재 선택된 TextBox
};

