#include "Mouse.h"
#include "TileDir.h"

#include <Actor/Wall.h>
#include <Actor/ActiveTile.h>
#include <Actor/ArrowTile.h>
#include <Actor/Goal.h>
#include <Actor/Enemy.h>
#include <Level/GameLevel.h>
#include <setTimer/Timer.h>
#include <Render/Renderer.h>


#include <iostream>
using namespace Craft;
Mouse::Mouse(const Craft::Vector2& position)
	: Actor(L"⯈", position, Color::BRIGHTWHITE),
	xPosition(GetPosition().x),
	yPosition(GetPosition().y), 
	timer(0.1f)
{
	sortingOrder = 3;
}

void Mouse::Tick(float deltaTime)
{
	super::Tick(deltaTime);
	Game& game = dynamic_cast<Game&>(Engine::Get());
	std::shared_ptr<GameLevel> level = Cast<GameLevel>(GetOwner());
	if (!level->GetisCanMove() && !isBreak)
	{
		// 쥐 움직이기 시작
		// 0. 타이머 체크(아직 이동 타이밍 아니면 리턴)
		timer.Tick(deltaTime);
		if (!timer.isTimeOut())
		{
			return;
		}

		//1. 골인지 확인: 맞다면 리턴
		if (isGoal(level))
		{
			level->SetMouseCount();
			//Engine::Get().PlayOnShot("Retro_Laser_Shot.wav");
			Engine::Get().PlayOnShot("pickupCoin.wav");


			if (level->GetMouseCount() == level->GetNumberOfMouse())
			{
				// 화면 바꾸기 Clear! 화면으로....
				level->SetisClear(true);
			}
			Destroy();
			return;
		}

		//2. 적인지 확인
		if (isEnemy(level))
		{
			
			// 사운드 효과 재생
			Engine::Get().PlayOnShot("Back.wav");
			//isBreak = true;
			game.GoToGameLevel();
			return;
		}
		// 현재 포지션 + 다음 포지션
		Vector2 newPosition = GetPosition() + MouseMoveDirChange();

		//3. CanMove(현재방향) 확인
		// 다음위치 검사햇을때 이동불가면 90도 회전
		while (!level->CanMove(GetPosition(), newPosition))
		{
			MousePrsp();
			newPosition = GetPosition() + MouseMoveDirChange();

		}
		//4. 화살표 타일 확인 → 방향만. 갱신
		ArrowTileUpdateDirectionFromTile(level);

		SetPosition(newPosition);
		timer.Reset();
	}
	
}

void Mouse::MousePrsp()
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


Vector2 Mouse::MouseMoveDirChange()
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

bool Mouse::isGoal(std::shared_ptr<GameLevel> level)
{
	auto mousePos = GetPosition() + MouseMoveDirChange();
	// 여기서 FindActorAt로 골 위치랑 같은위치인지 확인하고 맞다면 겜 클리어
	auto tiledir = level->FindActorAt<Goal>(mousePos);
	if (tiledir)
	{
		return true;
	}
	return false;
}

bool Mouse::isEnemy(std::shared_ptr<GameLevel> level)
{
	auto mousePos = GetPosition() + MouseMoveDirChange();
	// 여기서 AtPosition인가그걸로 골 위치랑 같은위치인지 확인하고 맞다면 겜 클리어 ㄱㄱ
	auto tiledir = level->FindActorAt<Enemy>(mousePos);
	if (tiledir)
	{
		return true;
	}
	return false;
}

void Mouse::ArrowTileUpdateDirectionFromTile(std::shared_ptr<GameLevel> level)
{
	auto mousePos = GetPosition() + MouseMoveDirChange();
	// ActiveTile이 맞다면 그 객체 포인터를 리턴한다. 
	auto tiledir = level->FindActorAt<ActiveTile>(mousePos);

	if (tiledir != nullptr)
	{
		OutputDebugStringA("FOUND\n");
		// 사운드 효과 재생
		Engine::Get().PlayOnShot("PushTile.wav");
		std::cout << "Mouse Pos: "
			<< mousePos.x << ", "
			<< mousePos.y << '\n';

		std::cout << "Tile Pos: "
			<< tiledir->GetPosition().x << ", "
			<< tiledir->GetPosition().y << '\n';

		direction = tiledir->GetDir();
		ChageArrowImage();
	}

}

void Mouse::ChageArrowImage()
{
	switch (direction)
	{
	case TileDir::Right: image = L"⯈";
		break;
	case TileDir::Left: image = L"⯇";
		break;
	case TileDir::Up: image = L"⯅";
		break;
	case TileDir::Down: image = L"⯆";
		break;
	}
}

