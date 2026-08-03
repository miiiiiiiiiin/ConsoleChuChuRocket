#include<iostream>
#include <Engine/Engine.h>
#include<Level/TestLevel.h>

int main()
{
	
	//테스트(2번째인자가 1번째인자의 자손이면 true)
	//auto isTestActorCHild 
	//	= std::is_base_of<Craft::Actor, TestActor>::value;
	//auto result = std::is_base_of<Craft::Actor, Craft::Level>::value;

	//std::enable_if_t<true, TestActor>;

	//std::cin.get();
	//
	Craft::Engine engine;
	engine.AddNewLevel<TestLevel>();
	engine.Run();
}