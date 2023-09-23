#include "stdafx.h"
#include "SceneManager.h"
#include "SceneType.h"
#include "SceneStage.h"
#include "SceneTitle.h"
#include "SceneClear.h"
#include "SceneGameOver.h"

SceneManager::SceneManager() : _currentSceneType(SceneType::TITLE)
{
	_scene = new SceneTitle();
}

SceneManager::~SceneManager()
{
	delete _scene;
}

//-----------------------------------------------------------------------------
/// @brief Scene�� ������ ������Ʈ�ϰ�, �� ��ȯ�� ���� �������� ó���� �Ѵ�.
//-----------------------------------------------------------------------------
void SceneManager::Run()
{
	_scene->Update();

	// Scene ��ȯ
	if (_isChanged)
	{
		delete _scene;

		switch (_currentSceneType)
		{
		case SceneType::TITLE:
			_scene = new SceneTitle();
			break;
		case SceneType::STAGE:
			_scene = new SceneStage();
			break;
		case SceneType::GAME_OVER:
			_scene = new SceneGameOver();
			break;
		case SceneType::CLEAR:
			_scene = new SceneClear();
			break;
		}

		_isChanged = false;
	}
	
}

//-----------------------------------------------------------------------------
/// @brief Scene�� ��ȯ�� ���ุ�ϰ� �������� ��ȯ�� Run���� �̷������.
///
/// @param scene ������ SceneType
//-----------------------------------------------------------------------------
void SceneManager::LoadScene(SceneType scene)
{
	_currentSceneType = scene;
	_isChanged = true;
}
