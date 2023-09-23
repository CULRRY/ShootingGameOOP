#pragma once

enum class	SceneType;
class		BaseScene;

class SceneManager
{
public:
	void Run();
	void LoadScene(SceneType scene);

private:
	BaseScene*	_scene;					///< ���� Scene ��ü
	SceneType	_currentSceneType;		///< ���� SceneType
	bool		_isChanged = false;		///< Scene�� ����Ǿ��ϴ��� Flag



//----------------------------------------------------------------------------
// Singleton
//----------------------------------------------------------------------------
private:
	SceneManager();
	~SceneManager();
public:
	static SceneManager* Instance()
	{
		if (_instance == nullptr)
		{
			_instance = new SceneManager();
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
	inline static SceneManager* _instance = nullptr;
};

