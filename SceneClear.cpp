#include "stdafx.h"
#include "SceneClear.h"

#include "Cursor.h"
#include "Game.h"
#include "ObjectManager.h"
#include "SceneManager.h"
#include "SceneType.h"
#include "TextBox.h"

SceneClear::SceneClear()
{
	Game::stage = 0;
	_cursor = new Cursor(8, 4, 8, 4, 10, 4);
	_title = new TextBox(4, 6, "Game Clear!");
	_menuTitle = new TextBox(8, 6, "Go To Start");
	_menuExit = new TextBox(10, 6, "Exit");

	ObjectManager::Instance()->CreateObject(_cursor);
	ObjectManager::Instance()->CreateObject(_title);
	ObjectManager::Instance()->CreateObject(_menuTitle);
	ObjectManager::Instance()->CreateObject(_menuExit);
}

SceneClear::~SceneClear()
{
	ObjectManager::Instance()->ClearObject();
}

void SceneClear::Update()
{
	_frameCount++;
	ProcessKeyboardInput();
	ObjectManager::Instance()->Update();
	ObjectManager::Instance()->Render();
}

void SceneClear::ProcessKeyboardInput()
{
	// 메뉴화면에서는 프레임 조정
	if (_frameCount % MENU_SELECT_FRAME != 0)
	{
		return;
	}
	// 위쪽 방향키.
	if (GetAsyncKeyState(VK_UP) & 0x8001)
	{
		_cursor->Move(-2, 0);
	}
	// 아래쪽 방향키.
	if (GetAsyncKeyState(VK_DOWN) & 0x8001)
	{
		_cursor->Move(2, 0);
	}

	// 엔터키
	if (GetAsyncKeyState(VK_RETURN) & 0x8001)
	{
		const BaseObject* selected = _cursor->SelectMenu();

		if (selected == _menuTitle)
		{
			SceneManager::Instance()->LoadScene(SceneType::TITLE);
		}
		else if (selected == _menuExit)
		{
			Game::Exit();
		}
	}
}
