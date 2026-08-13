#pragma once
#include <Level/Level.h>
class MainLevel : public Craft::Level
{
public:
	MainLevel();

	virtual void Tick(float deltaTime) override;
	virtual void Draw() override;

private:

};

