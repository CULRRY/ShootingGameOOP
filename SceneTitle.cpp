#include "stdafx.h"
#include "SceneTitle.h"
#include "Cursor.h"
#include "Game.h"
#include "ObjectManager.h"
#include "SceneManager.h"
#include "SceneType.h"
#include "ScreenBuffer.h"
#include "TextBox.h"

SceneTitle::SceneTitle()
{
	Game::stage = 0;
	_cursor = new Cursor(8, 4, 8, 4, 10, 4);
	_title = new TextBox(4, 6, "Shooting!");
	_menuStart = new TextBox(8, 6, "New Game");
	_menuExit = new TextBox(10, 6, "Exit");

	ObjectManager::Instance()->CreateObject(_cursor);
	ObjectManager::Instance()->CreateObject(_title);
	ObjectManager::Instance()->CreateObject(_menuStart);
	ObjectManager::Instance()->CreateObject(_menuExit);
}

SceneTitle::~SceneTitle()
{
	ObjectManager::Instance()->ClearObject();
}

void SceneTitle::Update()
{
	_frameCount++;
	ProcessKeyboardInput();
	ObjectManager::Instance()->Update();
	ObjectManager::Instance()->Render();
	
}

void SceneTitle::ProcessKeyboardInput()
{
	// �޴�ȭ�鿡���� ������ ����
	if (_frameCount % MENU_SELECT_FRAME != 0)
	{
		return;
	}
	// ���� ����Ű.
	if (GetAsyncKeyState(VK_UP) & 0x8001)
	{
		_cursor->Move(-2, 0);
	}
	// �Ʒ��� ����Ű.
	if (GetAsyncKeyState(VK_DOWN) & 0x8001)
	{
		_cursor->Move(2, 0);
	}

	// ����Ű
	if (GetAsyncKeyState(VK_RETURN) & 0x8001)
	{
		const BaseObject* selected = _cursor->SelectMenu();

		if (selected == _menuStart)
		{
			SceneManager::Instance()->LoadScene(SceneType::STAGE);
		}
		else if (selected == _menuExit)
		{
			Game::Exit();
		}
	}
}
