#pragma once
class Game
{
public:
	static constexpr int32	FPS_MS		= 20;
	static constexpr int32	MAX_STAGE	= 4;	///< 최고 스테이지

	inline static int32	stage		= 0;	///< 현재 스테이지
	inline static int32	currentFps	= 0;	///< 현재 초당 프레임

private:
	inline static bool	_isExit		= false;			///< 게임종료 여부

public:
	static void Run();
	static void Exit();
	
};

