#include "stdafx.h"
#include "DataLoader.h"

#include "Enemy.h"
#include "MovementInfo.h"
#include "ScreenBuffer.h"
#include "EnemyInfo.h"
#include "ObjectManager.h"

#include "Macro.h"

DataLoader::DataLoader()
{
	LoadMovementData();
	LoadEnemyData();
	LoadStageList();
}

DataLoader::~DataLoader()
{
	free(_enemyInfo);
	free(_movementInfo);
}

//-----------------------------------------------------------------------------
/// @brief EnemyId를 통해 enemy의 정보를 얻어온다.
///
/// @param id Data상의 EnemyId
/// @return 해당 Id의 Enemy정보들
//-----------------------------------------------------------------------------
EnemyInfo* DataLoader::GetEnemyInfo(int32 id)
{
	return &_enemyInfo[id];
}

//-----------------------------------------------------------------------------
/// @brief stage에 대한 정보를 얻어오고 스테이지를 세팅한다.
//-----------------------------------------------------------------------------
void DataLoader::LoadMovementData()
{
	FILE* file = nullptr;
	// 데이터 파일 리스트 오픈
	if (::fopen_s(&file, MOVEMENT_LIST_PATH, "r") != 0)
	{
		CRASH("파일 열기 에러");
	}

	char fileList[100][100] = { "", };

	int32 fileCount = 0;
	char fileName[100] = "";

	while (::fscanf_s(file, "%s", &fileName, (uint32)sizeof(fileName)) != EOF)
	{
		char path[100] = "data/movement/";
		::strcat_s(path, sizeof(path), fileName);
		::strcpy_s(fileList[fileCount], sizeof(path), path);
		fileCount++;
	}

	if (::fclose(file) != 0)
	{
		CRASH("파일 닫기 에러");
	}

	_movementInfo = (MovementInfo*)malloc(sizeof(MovementInfo) * fileCount);

	for (int32 i = 0; i < fileCount; i++)
	{
		if (::fopen_s(&file, fileList[i], "r") != 0)
		{
			CRASH("파일 열기 에러");
		}

		MovementInfo& info = _movementInfo[i];
		int32 movementCount = 0;
		while (::fscanf_s(file, "%d %d", &info.dy[movementCount], &info.dx[movementCount]) != EOF)
		{
			movementCount++;
		}
		info.size = movementCount;

		if (::fclose(file) != 0)
		{
			CRASH("파일 닫기 에러");
		}
	}
}


//-----------------------------------------------------------------------------
/// @brief Enemy의 데이터를 읽어와 메모리에 올린다.
//-----------------------------------------------------------------------------
void DataLoader::LoadEnemyData()
{
	FILE* file = nullptr;
	// 데이터 파일 리스트 오픈
	if (::fopen_s(&file, ENEMY_LIST_PATH, "r") != 0)
	{
		CRASH("파일 열기 에러");
	}

	char fileList[100][100] = { "", };

	int32 fileCount = 0;
	char fileName[100] = "";

	while (::fscanf_s(file, "%s", &fileName, (uint32)sizeof(fileName)) != EOF)
	{
		char path[100] = "data/enemy/";
		::strcat_s(path, sizeof(path), fileName);
		::strcpy_s(fileList[fileCount], sizeof(path), path);
		fileCount++;
	}

	if (::fclose(file) != 0)
	{
		CRASH("파일 닫기 에러");
	}

	_enemyInfo = (EnemyInfo*)malloc(sizeof(EnemyInfo) * fileCount);

	for (int32 i = 0; i < fileCount; i++)
	{
		if (::fopen_s(&file, fileList[i], "r") != 0)
		{
			CRASH("파일 열기 에러");
		}

		EnemyInfo& info = _enemyInfo[i];

		// 유닛 그래픽 불러오기
		for (int32 y = 0; y < 3; y++)
		{
			::fscanf_s(file, "%s", info.graphic[y], (uint32)sizeof(info.graphic[y]));
		}

		int32 movementId = 0;
		::fscanf_s(file, "%d", &_enemyInfo[i].hp);
		::fscanf_s(file, "%d", &_enemyInfo[i].attackFrequency);
		::fscanf_s(file, "%d", &_enemyInfo[i].bulletSpeed);
		::fscanf_s(file, "%d", &movementId);
		::fscanf_s(file, "%d", &_enemyInfo[i].moveSpeed);
		::fscanf_s(file, "%d", &_enemyInfo[i].moveDistance);

		_enemyInfo[i].movement.size = _movementInfo[movementId].size * _enemyInfo[i].moveDistance;

		// 움직임 정보 불러오기
		for (int32 moveInfoIdx = 0; moveInfoIdx < _movementInfo[movementId].size; moveInfoIdx++)
		{
			for (int32 iter = moveInfoIdx * _enemyInfo[i].moveDistance;
				iter < (moveInfoIdx + 1) * _enemyInfo[i].moveDistance;
				iter++)
			{
				_enemyInfo[i].movement.dy[iter] = _movementInfo[movementId].dy[moveInfoIdx];
				_enemyInfo[i].movement.dx[iter] = _movementInfo[movementId].dx[moveInfoIdx];
			}
		}

		// 총알 방향정보 불러오기
		int32 bulletIdx = 0;
		_enemyInfo[i].BulletCount = 0;
		while (::fscanf_s(file, "%d %d", &_enemyInfo[i].BulletXPosition[bulletIdx], &_enemyInfo[i].BulletDirection[bulletIdx])
			!= EOF)
		{
			if (bulletIdx > 3)
			{
				CRASH("총알 정보가 3개 초과함");
			}
			bulletIdx++;
			_enemyInfo[i].BulletCount++;
		}

		if (bulletIdx == 0)
		{
			CRASH("총알 정보 없음");
		}

		if (::fclose(file) != 0)
		{
			CRASH("파일 닫기 에러");
		}
	}
}

//-----------------------------------------------------------------------------
/// @brief StageData파일 목록을 읽어온다.
//-----------------------------------------------------------------------------
void DataLoader::LoadStageList()
{
	FILE* file = nullptr;
	// 데이터 파일 리스트 오픈
	if (::fopen_s(&file, STAGE_LIST_PATH, "r") != 0)
	{
		CRASH("파일 열기 에러");
	}


	int32 fileCount = 0;
	char fileName[100] = "";

	while (::fscanf_s(file, "%s", &fileName, (uint32)sizeof(fileName)) != EOF)
	{
		char path[100] = "data/stage/";
		::strcat_s(path, sizeof(path), fileName);
		::strcpy_s(_stageFileList[fileCount], sizeof(path), path);
		fileCount++;
	}

	if (::fclose(file) != 0)
	{
		CRASH("파일 닫기 에러");
	}
}




//-----------------------------------------------------------------------------
/// @brief 해당 스테이지의 대한 정보를 불러오고 세팅한다.
///
/// @param stage 불러올 스테이지 번호
//-----------------------------------------------------------------------------
void DataLoader::LoadStageData(int32 stage)
{
	FILE* file = nullptr;
	// 데이터 파일 리스트 오픈
	if (::fopen_s(&file, _stageFileList[stage], "r") != 0)
	{
		CRASH("파일 열기 에러");
	}

	char stageFileBuffer[ScreenBuffer::SCREEN_HEIGHT][ScreenBuffer::SCREEN_WIDTH] = { "", };

	// '=' '\n'넘기기
	fseek(file, ScreenBuffer::SCREEN_WIDTH + 2, SEEK_SET);

	for (int32 y = 0; y < ScreenBuffer::SCREEN_HEIGHT; y++)
	{
		fread_s(&stageFileBuffer[y], ScreenBuffer::SCREEN_WIDTH, 1, ScreenBuffer::SCREEN_WIDTH, file);
		stageFileBuffer[y][ScreenBuffer::SCREEN_WIDTH - 1] = 0;
		// '=' '\n'넘기기
		fseek(file, 2, SEEK_CUR);
	}

	if (::fclose(file) != 0)
	{
		CRASH("파일 닫기 에러");
	}

	for (int32 y = 0; y < ScreenBuffer::SCREEN_HEIGHT; y++)
	{
		for (int32 x = 0; x < ScreenBuffer::SCREEN_WIDTH; x++)
		{
			if (stageFileBuffer[y][x] == ' ' || stageFileBuffer[y][x] == 0)
			{
				continue;
			}

			// Object 생성
			ObjectManager::Instance()->CreateObject(new Enemy(y, x, stageFileBuffer[y][x] - '0'));
		}
	}
}


