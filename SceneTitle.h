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
	Cursor*		_cursor;		///< 커서
	TextBox*	_title;			///< 타이틀 텍스트
	TextBox*	_menuStart;		///< 게임시작 텍스트
	TextBox*	_menuExit;		///< 게임종료 텍스트
};

