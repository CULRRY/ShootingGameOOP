#pragma once
#include "BaseObject.h"

struct EnemyInfo;

class Enemy : public BaseObject
{
public:
	Enemy(int32 y, int32 x, int32 id);
	~Enemy() override;

	bool Update() override;
	void Render() override;

	bool IsCollision(BaseObject* other) override;
	void OnCollision(BaseObject* other) override;
	void Move(int dy, int dx);
	void Attack();

private:
	bool CanMoveCurrentFrame() const;
	bool CanAttackCurrentFrame() const;

private:
	int32				_hp;			///< 체력
	uint64				_movementCount;	///< 움직임 구현을 위한 카운트
	const EnemyInfo*	_info;			///< Enemy정보
};

