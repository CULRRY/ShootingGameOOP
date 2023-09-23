#pragma once
class BaseScene
{
public:
	BaseScene() : _frameCount(0)
	{
	}

	virtual ~BaseScene() {}

	/// @brief Scene의 로직을 업데이트한다.
	virtual void Update() = 0;

protected:
	/// @brief 키보드 인풋관련된 로직을 처리한다.
	virtual void ProcessKeyboardInput() = 0;

protected:
	uint64 _frameCount; ///< 메뉴선택에서 프레임을 조정하기 위한 FrameCount
};