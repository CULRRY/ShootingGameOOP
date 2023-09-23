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
	Player*		_player;		///< �÷��̾�
	TextBox*	_stageInfo;		///< �������� ����
	TextBox*	_fpsCount;		///< ���� ������ ���
	int32		_enemyCount;	///< ���� ���� ��

};

