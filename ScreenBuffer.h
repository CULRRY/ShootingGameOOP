#pragma once
class ScreenBuffer
{
public:
	static constexpr int32 SCREEN_HEIGHT	= 24;					///< ���� ��ũ�� ����
	static constexpr int32 SCREEN_WIDTH		= 81;					///< ���� ��ũ�� ����
	static constexpr int32 BUFFER_HEIGHT	= SCREEN_HEIGHT + 3;	///< ���� ����(UIĭ ����)
	static constexpr int32 BUFFER_WIDTH		= SCREEN_WIDTH;			///< ���� ����

public:
	void Flip();
	void Clear();
	void DrawSprite(int32 y, int32 x, char sprite);
	void DrawString(int32 y, int32 x, const char* string);

private:
	void MoveCursor(int32 y, int32 x);
	void ClearScreen();

private:
	HANDLE	_hConsole;
	char	_buffer[BUFFER_HEIGHT][BUFFER_WIDTH];



	//----------------------------------------------------------------------------
	// Singleton
	//----------------------------------------------------------------------------
private:
	ScreenBuffer();
	~ScreenBuffer();
public:
	static ScreenBuffer* Instance()
	{
		if (_instance == nullptr)
		{
			_instance = new ScreenBuffer();
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
	inline static ScreenBuffer* _instance = nullptr;
};

