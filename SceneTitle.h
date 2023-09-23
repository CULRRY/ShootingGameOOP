#pragma once
#include "BaseScene.h"

class Cursor;
class TextBox;

class SceneTitle : public BaseScene
{
	static constexpr int32 MENU_SELECT_FRAME = 10;
public:
	SceneTitle();
	~SceneTitle();

	void Update() override;

protected:
	void ProcessKeyboardInput() override;

private:
	Cursor*		_cursor;		///< Ŀ��
	TextBox*	_title;			///< Ÿ��Ʋ �ؽ�Ʈ
	TextBox*	_menuStart;		///< ���ӽ��� �ؽ�Ʈ
	TextBox*	_menuExit;		///< �������� �ؽ�Ʈ
};

