#pragma once
#include <Actor/Actor.h>
#include <Level/GameLevel.h>
#include <setTimer/Timer.h>
#include <vector>

class Enemy : public Craft::Actor
{
	TYPE_DECLARATIONS(Enemy, Actor)

public:
	Enemy(const Craft::Vector2& position);

	virtual void Tick(float deltaTime) override;
private:
	float xPosition = 0.0f;
	float yPosition = 0.0f;

	Timer timer;
	int EnemyCount = 0;

	// 장애물 움직임 상태변수
	bool isMinus = false;

	// 장애물 이미지 상태변수
	bool isReturn = false;
};

