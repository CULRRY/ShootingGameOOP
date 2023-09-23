#pragma once
#include "BaseScene.h"
class Player;
class TextBox;

class SceneStage : public BaseScene
{
public:
	SceneStage();
	~SceneStage() override;

	void Update() override;

protected:
	void ProcessKeyboardInput() override;
	void UpdateStageInfo();

protected:
	Player*		_player;		///< 플레이어
	TextBox*	_stageInfo;		///< 스테이지 정보
	TextBox*	_fpsCount;		///< 현재 프레임 출력
	int32		_enemyCount;	///< 남은 적군 수

};

