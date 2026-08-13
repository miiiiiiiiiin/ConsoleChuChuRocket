#pragma once
#include <Actor/Actor.h>
#include <Level/GameLevel.h>
#include <setTimer/Timer.h>
#include <vector>

class Enemy : public Craft::Actor
{
	TYPE_DECLARATIONS(Enemy, Actor)

public:
	Enemy(const std::vector<Craft::Vector2>& EnemyList);

	// 조건에 맞게 몬스터 움직임 인덱스 바꾸는 함수
	int setEnemyCount();

	virtual void Tick(float deltaTime) override;
private:
	float xPosition = 0.0f;
	float yPosition = 0.0f;

	Timer timer;
	int EnemyCount = 0;
	const std::vector<Craft::Vector2> EnemyVector;

	bool isMinus = false;
};

