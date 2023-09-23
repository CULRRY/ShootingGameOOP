#pragma once
#include "BaseScene.h"

class Cursor;
class TextBox;

class SceneClear : public BaseScene
{
	static constexpr int32 MENU_SELECT_FRAME = 10;
public:
	SceneClear();
	~SceneClear() override;

	void Update() override;

protected:
	void ProcessKeyboardInput() override;

protected:
	Cursor*		_cursor;		///< Ŀ��
	TextBox*	_title;			///< Ÿ��Ʋ �ؽ�Ʈ
	TextBox*	_menuTitle;		///< ����ȭ������ ���� �ؽ�Ʈ
	TextBox*	_menuExit;		///< �������� �ؽ�Ʈ
};

