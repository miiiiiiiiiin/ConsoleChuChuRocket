#include "Cat.h"
#include "TileDir.h"

#include <Actor/Wall.h>
#include <Actor/ActiveTile.h>
#include <Actor/ArrowTile.h>
#include <Actor/Goal.h>
#include <Actor/Enemy.h>
#include <Actor/Mouse.h>
#include <Level/GameLevel.h>
#include <setTimer/Timer.h>
#include <Render/Renderer.h>


#include <iostream>
using namespace Craft;

Cat::Cat(const Craft::Vector2& position)
	: Actor(L"⯇", position, Color::RED),
	xPosition(GetPosition().x),
	yPosition(GetPosition().y),
	timer(0.2f)
{
	sortingOrder = 5;
	//timer.SetTargetTime(0.5f);
}

void Cat::Tick(float deltaTime)
{
	super::Tick(deltaTime);
	Game& game = dynamic_cast<Game&>(Engine::Get());
	std::shared_ptr<GameLevel> level = Cast<GameLevel>(GetOwner());
	if (!level->GetisCanMove() && !isBreak)
	{
		//CatMove(deltaTime);
		// 쥐 움직이기 시작
		// 0. 타이머 체크(아직 이동 타이밍 아니면 리턴)
		timer.Tick(deltaTime);
		if (!timer.isTimeOut())
		{
			return;
		}
		//1. 골인지 확인: 맞다면 게임오버
		if (isBump<Goal>(level, game))
			game.GoToGameLevel();
		// 2. 장애물(적)인지 확인
		if (isBump<Enemy>(level, game))
		{
			Destroy();
			return;
		}
		// 3. 쥐인지 확인
		if(isBump<Mouse>(level, game)) game.GoToGameLevel();

		Vector2 newPosition = GetPosition() + CatMoveDirChange();

		// 4. 벽 부딪혔다면 시계방향으로 방향 갱신
		while (!level->CanMove(GetPosition(), newPosition))
		{
			CatPrsp();
			newPosition = GetPosition() + CatMoveDirChange();

		}
		//5. 화살표 타일 확인 → 방향 갱신
		ArrowTileUpdateDirectionFromTile(level, newPosition);

		// 6. 이동 확정
		SetPosition(newPosition);
		timer.Reset();
	}

}

void Cat::CatPrsp()
{
	switch (direction)
	{
	case TileDir::Right:
		direction = TileDir::Down;
		image = L"⯆";
		break;
	case TileDir::Left:
		direction = TileDir::Up;
		image = L"⯅";
		break;
	case TileDir::Up:
		direction = TileDir::Right;
		image = L"⯈";
		break;
	case TileDir::Down:
		direction = TileDir::Left;
		image = L"⯇";
		break;
	}
}


Vector2 Cat::CatMoveDirChange()
{
	switch (direction)
	{
	case TileDir::Up:    return Vector2(0, -1);
	case TileDir::Down:  return Vector2(0, 1);
	case TileDir::Left:  return Vector2(-1, 0);
	case TileDir::Right: return Vector2(1, 0);
	}
	return Vector2(0, 0);

}

template<typename T>
bool Cat::isBump(std::shared_ptr<GameLevel> level, Game& game)
{
	auto CatPos = GetPosition() + CatMoveDirChange();
	// 여기서 FindActorAt로 충돌확인
	auto tiledir = level->FindActorAt<T>(CatPos);
	if (tiledir)
	{
		// 사운드 효과 재생
		Engine::Get().PlayOnShot("hitHurt.wav");
		return true;
	}
	return false;
}

void Cat::ArrowTileUpdateDirectionFromTile(std::shared_ptr<GameLevel> level, Vector2& newPosition)
{
	//auto CatPos = GetPosition() + CatMoveDirChange();
	// ActiveTile이 맞다면 그 객체 포인터를 리턴한다. 
	auto tiledir = level->FindActorAt<ActiveTile>(newPosition);

	if (tiledir != nullptr)
	{
		direction = tiledir->GetDir();

	}
}