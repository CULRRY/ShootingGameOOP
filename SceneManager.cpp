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
/// @brief Scene의 로직을 업데이트하고, 씬 전환에 대한 실질적인 처리도 한다.
//-----------------------------------------------------------------------------
void SceneManager::Run()
{
	_scene->Update();

	// Scene 전환
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
/// @brief Scene을 전환할 예약만하고 실질적인 전환은 Run에서 이루어진다.
///
/// @param scene 변경할 SceneType
//-----------------------------------------------------------------------------
void SceneManager::LoadScene(SceneType scene)
{
	_currentSceneType = scene;
	_isChanged = true;
}
