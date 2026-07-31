#include "TestActor.h"
#include<iostream>
#include<Windows.h>

using namespace Craft;
void TestActor::Tick(float deltaTime)
{
	//상위 로직 호출
	Actor::Tick(deltaTime);

	//TODO: 임시 처리
	//esc 누르면 종료
	if ((GetAsyncKeyState(VK_ESCAPE) & 0x8000) != 0)
	{
		//엔진 종료
		QuitGame();
	}

	std::cout << "TestActor: Tick() - deltaTime: " << deltaTime
	<< "| FPS: " << (1.0f / deltaTime) << "\n";
}
