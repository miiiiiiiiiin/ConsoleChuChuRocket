#include "Game.h"
#include <Level/ClearLevel.h>
#include <Level/GameLevel.h>
#include <Level/MainLevel.h>
#include <Level/MenuLevel.h>

Game::Game() : timer(1.5f)
{
	// 두 레벨 생성 및 배열에 추가
	levelList.emplace_back(std::make_shared<MainLevel>());
	levelList.emplace_back(std::make_shared<GameLevel>());
	levelList.emplace_back(std::make_shared<MenuLevel>());
	levelList.emplace_back(std::make_shared<ClearLevel>());

	// 시작 상태 설정
	state = State::Main;

	// 게임 시작 시 활성화할 레벨 설정 
	// Todo: 메인화면 제작 후 메인화면으로 바꾸기
	mainLevel = levelList[(int)state];
}

void Game::MainToGame()
{ // 메인: 0 게임: 1
	mainLevel = levelList[1];
	state = static_cast<State>(1);
}

void Game::GoToClearLevel()
{
	// 사운드 효과 재생
	Engine::Get().PlayOnShot("pickupCoin.wav");
	mainLevel = levelList[3];   // ClearLevel 인덱스
	state = State::Clear;
	timer.Reset();
	timer.SetTargetTime(1.5f);
}

void Game::GoToGameLevel()
{
	AddNewLevel<GameLevel>();   // GameLevel 인덱스
	state = State::Game;
}

void Game::ToggleGameToMenu()
{ // 겜: 1 메뉴 : 2
	int stateIndex = static_cast<int>(state);

	int nextState = stateIndex == 2 ? 1 : 2;

	// 레벨 설정 및 상태 값 업데이트
	mainLevel = levelList[nextState];
	state = static_cast<State>(nextState);
}

void Game::MenuToMain()
{ // 메뉴 : 2 메인: 0
	mainLevel = levelList[0];
	state = static_cast<State>(0);
}
