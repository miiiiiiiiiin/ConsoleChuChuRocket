#pragma once
#include<Actor/Actor.h>
#include<Windows.h>

//테스트용 액터
class TestActor : public Craft::Actor
{
	
public:
	TestActor();
	~TestActor();
	virtual void Tick(float deltaTime) override;
	
};

