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
	Cursor*		_cursor;		///< 커서
	TextBox*	_title;			///< 타이틀 텍스트
	TextBox*	_menuTitle;		///< 시작화면으로 가기 텍스트
	TextBox*	_menuExit;		///< 게임종료 텍스트
};

