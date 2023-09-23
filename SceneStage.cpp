#include "stdafx.h"
#include "SceneStage.h"
#include "Player.h"
#include "TextBox.h"
#include "Game.h"
#include "ObjectManager.h"
#include "ScreenBuffer.h"
#include "BulletPlayer.h"
#include "DataLoader.h"
#include "SceneManager.h"
#include "SceneType.h"


SceneStage::SceneStage() : _enemyCount(0)
{
	_player = new Player();
	_stageInfo = new TextBox(ScreenBuffer::SCREEN_HEIGHT, 0, "");
	_fpsCount = new TextBox(ScreenBuffer::SCREEN_HEIGHT + 1, 0, "");
	ObjectManager::Instance()->CreateObject(_player);
	ObjectManager::Instance()->CreateObject(_stageInfo);
	ObjectManager::Instance()->CreateObject(_fpsCount);
	DataLoader::Instance()->LoadStageData(Game::stage);
}

SceneStage::~SceneStage()
{
	ObjectManager::Instance()->ClearObject();
}

void SceneStage::Update()
{
	_frameCount++;
	ProcessKeyboardInput();
	UpdateStageInfo();
	ObjectManager::Instance()->Update();
	ObjectManager::Instance()->Render();

	_enemyCount = ObjectManager::Instance()->GetCountByObjectType(ObjectType::ENEMY);
	// 적군 다죽임
	if (_enemyCount == 0)
	{
		Game::stage++;

		if (Game::stage == Game::MAX_STAGE)
		{
			SceneManager::Instance()->LoadScene(SceneType::CLEAR);
		}
		else
		{
			SceneManager::Instance()->LoadScene(SceneType::STAGE);
		}
	}

	// 플레이어 사망
	if (_player->IsSurvive() == false)
	{
		SceneManager::Instance()->LoadScene(SceneType::GAME_OVER);
	}

}

void SceneStage::ProcessKeyboardInput()
{
	if (_player->CanMoveCurrentFrame())
	{
		// 위쪽 방향키.
		if (GetAsyncKeyState(VK_UP) & 0x8001)
		{
			_player->Move(-1, 0);
		}
		// 아래쪽 방향키.
		if (GetAsyncKeyState(VK_DOWN) & 0x8001)
		{
			_player->Move(1, 0);
		}
		// 왼쪽 방향키.
		if (GetAsyncKeyState(VK_LEFT))
		{
			_player->Move(0, -1);
		}
		// 오른쪽 방향키.
		if (GetAsyncKeyState(VK_RIGHT))
		{
			_player->Move(0, 1);
		}
	}

	// 콘트롤 키. (미사일 키)
	if (GetAsyncKeyState(VK_CONTROL))
	{
		if (_player->CanAttackCurrentFrame())
			_player->Attack();
	}
}

//-----------------------------------------------------------------------------
/// @brief UI창에 출력되는 정보 텍스트를 업데이트한다.
//-----------------------------------------------------------------------------
void SceneStage::UpdateStageInfo()
{
	char stageInfo[50];
	sprintf_s(stageInfo, "STAGE %d | HP %2d / %2d | LEFT : %2d", 
		Game::stage + 1, 
		_player->GetCurrentHp(), 
		_player->GetMaxHp(), 
		_enemyCount
	);

	_stageInfo->ChangeText(stageInfo);

	char fpsInfo[10];
	sprintf_s(fpsInfo, "FPS : %d", Game::currentFps);
	_fpsCount->ChangeText(fpsInfo);
}
