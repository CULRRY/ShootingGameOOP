#pragma once
#include "BaseObject.h"

class Player : public BaseObject
{
public:
	Player();
	~Player() override;
	bool Update() override;
	void Render() override;


	bool IsCollision(BaseObject* other) override;
	void OnCollision(BaseObject* other) override;

	void Move(int dy, int dx);
	void Attack();
	bool IsSurvive();

	bool CanMoveCurrentFrame();
	bool CanAttackCurrentFrame();

	const int32 GetCurrentHp()
	{
		return _hp;
	}

	const int32 GetMaxHp()
	{
		return _maxHp;
	}

protected:
	int32 _maxHp;				///< 최대 체력
	int32 _hp;					///< 체력
	int32 _moveSpeed;			///< 이동속도
	int32 _attackFrequency;		///< 공격속도
	int32 _bulletSpeed;			///< 총알속도
};

