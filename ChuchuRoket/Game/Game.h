#pragma once
#include <Level/Level.h>
#include <Engine/Engine.h>
#include <vector>
#include <setTimer/Timer.h>
enum class State
{
	Main = 0,
	Game = 1,
	Menu,
	Clear	
};

class Game : public Craft::Engine
{
public:
	Game();
	~Game() = default;

	// 메인화면 -> 게임화면
	void MainToGame();

	// 겜 -> 클리어 ㄱㄱ
	void GoToClearLevel();

	// 클리어 -> 겜
	void GoToGameLevel();

	// 게임화면 <-> 메뉴 화면
	void ToggleGameToMenu();

	// 메뉴에서 메인으로
	void MenuToMain();

public:
	// 게터세터
	bool GetisClear() const { return isClear; }
	void SetisClear(bool clear) { isClear = clear; }

	void ResetTime() { timer.Reset(); }
	void SetTimer(float time) { timer.SetTargetTime(time); }
	void SetTick(float time) { timer.Tick(time); }
	bool GetisTimeOut() const { return timer.isTimeOut(); }

	// 스테이지넘버 겟셋
	int GetStageNum() const { return StageNum; }
	void SetStageNum(int stagenum) { StageNum = stagenum; }
	void StageNumCounting() { StageNum++; }

private:
	std::vector <std::shared_ptr<Craft::Level>> levelList;

	State state = State::Game;

	// 게임 클리어인지 확인하는 변수
	bool isClear = false;

	// 클리어 화면용 시간 계산
	Timer timer;

	// 게임레벨의 스테이지넘버
	int StageNum = 1;

};

