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
/// @brief EnemyId�� ���� enemy�� ������ ���´�.
///
/// @param id Data���� EnemyId
/// @return �ش� Id�� Enemy������
//-----------------------------------------------------------------------------
EnemyInfo* DataLoader::GetEnemyInfo(int32 id)
{
	return &_enemyInfo[id];
}

//-----------------------------------------------------------------------------
/// @brief stage�� ���� ������ ������ ���������� �����Ѵ�.
//-----------------------------------------------------------------------------
void DataLoader::LoadMovementData()
{
	FILE* file = nullptr;
	// ������ ���� ����Ʈ ����
	if (::fopen_s(&file, MOVEMENT_LIST_PATH, "r") != 0)
	{
		CRASH("���� ���� ����");
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
		CRASH("���� �ݱ� ����");
	}

	_movementInfo = (MovementInfo*)malloc(sizeof(MovementInfo) * fileCount);

	for (int32 i = 0; i < fileCount; i++)
	{
		if (::fopen_s(&file, fileList[i], "r") != 0)
		{
			CRASH("���� ���� ����");
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
			CRASH("���� �ݱ� ����");
		}
	}
}


//-----------------------------------------------------------------------------
/// @brief Enemy�� �����͸� �о�� �޸𸮿� �ø���.
//-----------------------------------------------------------------------------
void DataLoader::LoadEnemyData()
{
	FILE* file = nullptr;
	// ������ ���� ����Ʈ ����
	if (::fopen_s(&file, ENEMY_LIST_PATH, "r") != 0)
	{
		CRASH("���� ���� ����");
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
		CRASH("���� �ݱ� ����");
	}

	_enemyInfo = (EnemyInfo*)malloc(sizeof(EnemyInfo) * fileCount);

	for (int32 i = 0; i < fileCount; i++)
	{
		if (::fopen_s(&file, fileList[i], "r") != 0)
		{
			CRASH("���� ���� ����");
		}

		EnemyInfo& info = _enemyInfo[i];

		// ���� �׷��� �ҷ�����
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

		// ������ ���� �ҷ�����
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

		// �Ѿ� �������� �ҷ�����
		int32 bulletIdx = 0;
		_enemyInfo[i].BulletCount = 0;
		while (::fscanf_s(file, "%d %d", &_enemyInfo[i].BulletXPosition[bulletIdx], &_enemyInfo[i].BulletDirection[bulletIdx])
			!= EOF)
		{
			if (bulletIdx > 3)
			{
				CRASH("�Ѿ� ������ 3�� �ʰ���");
			}
			bulletIdx++;
			_enemyInfo[i].BulletCount++;
		}

		if (bulletIdx == 0)
		{
			CRASH("�Ѿ� ���� ����");
		}

		if (::fclose(file) != 0)
		{
			CRASH("���� �ݱ� ����");
		}
	}
}

//-----------------------------------------------------------------------------
/// @brief StageData���� ����� �о�´�.
//-----------------------------------------------------------------------------
void DataLoader::LoadStageList()
{
	FILE* file = nullptr;
	// ������ ���� ����Ʈ ����
	if (::fopen_s(&file, STAGE_LIST_PATH, "r") != 0)
	{
		CRASH("���� ���� ����");
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
		CRASH("���� �ݱ� ����");
	}
}




//-----------------------------------------------------------------------------
/// @brief �ش� ���������� ���� ������ �ҷ����� �����Ѵ�.
///
/// @param stage �ҷ��� �������� ��ȣ
//-----------------------------------------------------------------------------
void DataLoader::LoadStageData(int32 stage)
{
	FILE* file = nullptr;
	// ������ ���� ����Ʈ ����
	if (::fopen_s(&file, _stageFileList[stage], "r") != 0)
	{
		CRASH("���� ���� ����");
	}

	char stageFileBuffer[ScreenBuffer::SCREEN_HEIGHT][ScreenBuffer::SCREEN_WIDTH] = { "", };

	// '=' '\n'�ѱ��
	fseek(file, ScreenBuffer::SCREEN_WIDTH + 2, SEEK_SET);

	for (int32 y = 0; y < ScreenBuffer::SCREEN_HEIGHT; y++)
	{
		fread_s(&stageFileBuffer[y], ScreenBuffer::SCREEN_WIDTH, 1, ScreenBuffer::SCREEN_WIDTH, file);
		stageFileBuffer[y][ScreenBuffer::SCREEN_WIDTH - 1] = 0;
		// '=' '\n'�ѱ��
		fseek(file, 2, SEEK_CUR);
	}

	if (::fclose(file) != 0)
	{
		CRASH("���� �ݱ� ����");
	}

	for (int32 y = 0; y < ScreenBuffer::SCREEN_HEIGHT; y++)
	{
		for (int32 x = 0; x < ScreenBuffer::SCREEN_WIDTH; x++)
		{
			if (stageFileBuffer[y][x] == ' ' || stageFileBuffer[y][x] == 0)
			{
				continue;
			}

			// Object ����
			ObjectManager::Instance()->CreateObject(new Enemy(y, x, stageFileBuffer[y][x] - '0'));
		}
	}
}


