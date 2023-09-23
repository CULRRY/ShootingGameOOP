#pragma once
#define MOVEMENT_LIST_PATH	"data/movement/list.dat"
#define ENEMY_LIST_PATH		"data/enemy/list.dat"
#define STAGE_LIST_PATH		"data/stage/list.dat"

struct EnemyInfo;
struct MovementInfo;

class DataLoader
{

public:
	EnemyInfo*	GetEnemyInfo(int32 id);
	void		LoadStageData(int32 stage);

private:
	void		LoadMovementData();
	void		LoadEnemyData();
	void		LoadStageList();

private:
	EnemyInfo*		_enemyInfo;					///< enemyInfo 리스트
	MovementInfo*	_movementInfo;				///< movementInfo 리스트
	char			_stageFileList[100][100];	///< StageData 파일 목록



	//----------------------------------------------------------------------------
	// Singleton
	//----------------------------------------------------------------------------
private:
	DataLoader();
	~DataLoader();
public:
	static DataLoader* Instance()
	{
		if (_instance == nullptr)
		{
			_instance = new DataLoader();
			::atexit(Destroy);
		}

		return _instance;
	}

	static void Destroy()
	{
		delete _instance;
		_instance = nullptr;
	}
private:
	inline static DataLoader* _instance = nullptr;


};

