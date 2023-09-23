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
	int32			_maxY;							///< Ŀ���� �̵������� �ִ� Y��ǥ
	int32			_minY;							///< Ŀ���� �̵������� �ּ� Y��ǥ
	int32			_maxX;							///< Ŀ���� �̵������� �ִ� X��ǥ
	int32			_minX;							///< Ŀ���� �̵������� �ּ� X��ǥ
	BaseObject*		_currentSelectedMenu = nullptr;	///< ���� ���õ� TextBox
};

