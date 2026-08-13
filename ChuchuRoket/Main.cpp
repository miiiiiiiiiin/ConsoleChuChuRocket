#include <Engine/Engine.h>
#include <Level/GameLevel.h>
#include <Game/Game.h>
int main()
{
	// 엔진 객체 생성 및 실행
	//Craft::Engine engine;
	//engine.AddNewLevel<GameLevel>();
	//engine.Run();
	Game game;
	game.Run();
}