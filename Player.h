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
	int32 _maxHp;				///< �ִ� ü��
	int32 _hp;					///< ü��
	int32 _moveSpeed;			///< �̵��ӵ�
	int32 _attackFrequency;		///< ���ݼӵ�
	int32 _bulletSpeed;			///< �Ѿ˼ӵ�
};

