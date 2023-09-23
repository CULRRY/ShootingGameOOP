#pragma once
#include "Bullet.h"

class BulletEnemy : public Bullet
{
	static constexpr int32 DELTA_X[3] = { -1, 0, 1 }; ///< ���⿡ ���� X�̵� ����

public:
	BulletEnemy(int32 y, int32 x, BulletDirection dir, int32 speed);
	~BulletEnemy() override;

	bool Update() override;
	void Render() override;
	void OnCollision(BaseObject* other) override;

	bool move() override;
};

