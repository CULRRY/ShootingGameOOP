#pragma once
#include "Bullet.h"

class BulletPlayer : public Bullet
{
public:
	BulletPlayer(int32 y, int32 x, BulletDirection dir, int32 speed);
	~BulletPlayer() override;

	bool Update() override;
	void Render() override;
	void OnCollision(BaseObject* other) override;

	bool move() override;
};

