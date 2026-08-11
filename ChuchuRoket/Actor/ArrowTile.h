#pragma once
#include <Actor/Actor.h>
#include <Level/GameLevel.h>

class ArrowTile : public Craft::Actor
{
	TYPE_DECLARATIONS(ArrowTile, Actor)

	// 화살표 방향
	enum TileDir
	{
		Left,
		Right,
		Up,
		Down
	};

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

private:
	// 타일 방향 정보
	TileDir tileDir = TileDir::Left;

	// 

};

