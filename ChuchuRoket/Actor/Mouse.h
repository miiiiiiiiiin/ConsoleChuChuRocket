#pragma once
#include "TileDir.h"
#include<Level/Level.h>
#include<Actor/Actor.h>
#include <Level/GameLevel.h>
#include <setTimer/Timer.h>

class Mouse : public Craft::Actor
{
	TYPE_DECLARATIONS(Mouse, Actor)

	//현재 쥐가 바라보는 방향. 타일의 방향 정보와 비교하여 변경한다.

public:
	Mouse(const Craft::Vector2& position);

private:

	virtual void Tick(float deltaTime) override;

	//쥐가 바라보고 있는 방향 설정. 
	//벽 부딪히면 90회전
	void MousePrsp();

	// 플래그 뜨면 쥐 이동
	// 기호 방향에 맞춰서 직진 이동 함수
	// Dir: 
	Craft::Vector2 MouseMoveDirChange();

	// 골인지 확인하는 함수
	bool isGoal(std::shared_ptr<GameLevel> level);

	// 몬스터인지 확인하는 함수
	bool isEnemy(std::shared_ptr<GameLevel> level);

	// 화살표 타일 방향 확인 함수
	void ArrowTileUpdateDirectionFromTile(std::shared_ptr<GameLevel> level);

	//  타일에 맞는 방향이미지 설정하기
	void ChageArrowImage();

	// 쥐 방향 세터
	void SetDir(TileDir dir) { direction = dir; }
private:
	//현재 위치
	Craft::Vector2 position;

	// 쥐가 바라보는 방향
	TileDir direction = TileDir::Right;

	//y 이동 변수
	float yPosition;

	// x 이동 변수
	float xPosition;

	// 이동 속도
	float moveSpeed = 3.0f;

	//시작되었다면 Tick 실행
	bool isBreak = false;

	Timer timer;
	Timer infiniteMouseTime;

};

