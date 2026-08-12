#pragma once
#include <Actor/Actor.h>
#include <Level/GameLevel.h>
#include "TileDir.h"

class ArrowTile : public Craft::Actor
{
	TYPE_DECLARATIONS(ArrowTile, Actor)

	

public:
	ArrowTile(const Craft::Vector2& position);
	virtual void Tick(float deltaTime) override;



private:
	// wasd 이동
	Craft::Vector2 ArrowMove(
		Craft::Vector2 dir, 
		Craft::Vector2 nowPos, 
		std::shared_ptr<GameLevel> level
	);

	// 방향키 변경: 이미지 변경, tileDir변경
	void ArrowSelect(std::wstring str, TileDir dir);

	// 방향타일 횟수 검사해서 다했느면 isGame= true로 바꾸는함수
	bool canStart(std::shared_ptr<GameLevel> gamelevel);

	// Mouse에서 쓸 Getter
	bool GetCanMove() { return CanMove; }

private:
	// 타일 방향 정보
	TileDir tileDir = TileDir::Left;

	// 이동 가능한지 확인
	bool CanMove = true;

	// 맨 처음 위치
	Craft::Vector2 startPosition;



	

};

