#pragma once
class Game
{
public:
	static constexpr int32	FPS_MS		= 20;
	static constexpr int32	MAX_STAGE	= 4;	///< �ְ� ��������

	inline static int32	stage		= 0;	///< ���� ��������
	inline static int32	currentFps	= 0;	///< ���� �ʴ� ������

private:
	inline static bool	_isExit		= false;			///< �������� ����

public:
	static void Run();
	static void Exit();
	
};

