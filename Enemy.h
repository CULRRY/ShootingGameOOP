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
	int32				_hp;			///< ü��
	uint64				_movementCount;	///< ������ ������ ���� ī��Ʈ
	const EnemyInfo*	_info;			///< Enemy����
};

