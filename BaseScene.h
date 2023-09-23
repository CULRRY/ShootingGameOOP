#pragma once
class BaseScene
{
public:
	BaseScene() : _frameCount(0)
	{
	}

	virtual ~BaseScene() {}

	/// @brief Scene�� ������ ������Ʈ�Ѵ�.
	virtual void Update() = 0;

protected:
	/// @brief Ű���� ��ǲ���õ� ������ ó���Ѵ�.
	virtual void ProcessKeyboardInput() = 0;

protected:
	uint64 _frameCount; ///< �޴����ÿ��� �������� �����ϱ� ���� FrameCount
};