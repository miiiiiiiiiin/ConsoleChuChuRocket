#pragma once
#include<Actor/Actor.h>

//테스트용 액터
class TestActor : public Craft::Actor
{
public:
	virtual void Tick(float deltaTime) override;

};

