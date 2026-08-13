#pragma once
#include <Actor/Actor.h>
#include <Level/GameLevel.h>
#include <setTimer/Timer.h>
#include <vector>

#include "TileDir.h"

class Enemy : public Craft::Actor
{
	TYPE_DECLARATIONS(Enemy, Actor)

public:
	Enemy(const std::vector<Craft::Vector2>& EnemyList);
	int setEnemyCount();
	// 
	virtual void Tick(float deltaTime) override;
private:
	TileDir tile = TileDir::Down;

	float xPosition = 0.0f;
	float yPosition = 0.0f;

	Timer timer;
	int EnemyCount = 0;
	const std::vector<Craft::Vector2> EnemyVector;

	bool isMinus = false;
};

