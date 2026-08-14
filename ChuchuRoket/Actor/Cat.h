#pragma once
#include "TileDir.h"
#include<Level/Level.h>
#include<Actor/Actor.h>
#include <Level/GameLevel.h>
#include <setTimer/Timer.h>

// 고양이 적 로직 설명
// 고양이는 벽에 부딪히면 시계방향 90도 회전한다. 
// 갈 곳이 없게 되면 가만히 있는다.
// 고양이는 쥐보다 느리다.
// 고양이가 장애물에 부딪히면 고양이 Destroy
// 쥐와 부딪히면 게임 오버.
// 고양이가 먼저 골에 도착하면 게임 오버.
class Cat : public Craft::Actor
{
	TYPE_DECLARATIONS(Cat, Actor)

public:
	Cat(const Craft::Vector2& position);

private:

	virtual void Tick(float deltaTime) override;

	//고양이가 바라보고 있는 방향 설정. 
	//벽 부딪히면 90회전
	void CatPrsp();

	// 플래그 뜨면 고양이 이동
	// 기호 방향에 맞춰서 직진 이동 함수
	// Dir: 
	Craft::Vector2 CatMoveDirChange();

	// 몬스터인지 확인하는 함수
	template<typename T>
	bool isBump(std::shared_ptr<GameLevel> level, Game& game);

	// 화살표 타일 방향 확인 함수
	void ArrowTileUpdateDirectionFromTile(std::shared_ptr<GameLevel> level);

	// 고양이 방향 세터
	void SetDir(TileDir dir) { direction = dir; }
private:
	//현재 위치
	Craft::Vector2 position;

	// 고양이가 바라보는 방향
	TileDir direction = TileDir::Left;

	//y 이동 변수
	float yPosition;

	// x 이동 변수
	float xPosition;

	// 이동 속도
	float moveSpeed = 3.0f;

	//시작되었다면 Tick 실행
	bool isBreak = false;

	Timer timer;
	Timer infiniteCatTime;
};

