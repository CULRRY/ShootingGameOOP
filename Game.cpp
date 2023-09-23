#include "stdafx.h"
#include "Game.h"

#include "SceneManager.h"

//-----------------------------------------------------------------------------
/// @brief 게임 실행
//-----------------------------------------------------------------------------
void Game::Run()
{
	DWORD startTime = timeGetTime();
	DWORD timeForFPS = startTime;
	DWORD idealTime = startTime;

	int32 frame = 0;
	DWORD overTime = 0;
	while(true)
	{
		frame++;
		if (timeGetTime() - timeForFPS >= 1000)
		{
			currentFps = frame;
			frame = 0;
			timeForFPS += 1000;
		}
		SceneManager::Instance()->Run();

		if (_isExit)
			return;

		// 50프레임 고정
		Sleep(FPS_MS - overTime);

		idealTime += FPS_MS;
		overTime = timeGetTime() - idealTime;

		if (overTime <= 0)
			overTime = 0;
		else if (overTime >= FPS_MS)
			overTime = FPS_MS;
	}
}

//-----------------------------------------------------------------------------
/// @brief 게임 종료
//-----------------------------------------------------------------------------
void Game::Exit()
{
	_isExit = true;
}
