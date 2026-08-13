#pragma once
#include <Level/Level.h>
#include <setTimer/Timer.h>
#include <Game/Game.h>
#include <Engine/Engine.h>
class ClearLevel : public Craft::Level
{
public:
	ClearLevel();
	virtual void OnInitialized() override;
	virtual void Tick(float deltaTime) override;
	virtual void Draw() override;
private:
	Timer timer;
};

