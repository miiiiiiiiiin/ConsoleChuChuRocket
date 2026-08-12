#include "Mouse.h"
#include "TileDir.h"

#include <Actor/Wall.h>
#include <Actor/ActiveTile.h>
#include <Level/GameLevel.h>
#include <setTimer/Timer.h>

using namespace Craft;
Mouse::Mouse(const Craft::Vector2& position)
	: Actor(L"⯈", position, Color::BRIGHTWHITE),
	xPosition(GetPosition().x),
	yPosition(GetPosition().y), 
	timer(0.5f)

{
	sortingOrder = 5;
	//timer.SetTargetTime(0.5f);
}

void Mouse::Tick(float deltaTime)
{
	super::Tick(deltaTime);
	// Todo: 시작버튼 누르면 Tick 활성화되게 하기
	if (isStart)
	{
		//MouseMove(deltaTime);

		//1. 타이머 체크(아직 이동 타이밍 아니면 리턴)
		timer.Tick(deltaTime);
		if (!timer.isTimeOut())
		{
			return;
		}

		std::shared_ptr<GameLevel> level = Cast<GameLevel>(GetOwner());

		//2. 화살표 타일 확인 → 방향 갱신
		ArrowTileUpdateDirectionFromTile(level);

		//3. CanMove(현재방향) 확인
		Vector2 newPosition = GetPosition() + MouseMoveDirChange();

		// 다음위치 검사햇을때 이동불가면 90도 회전
		if (!level->CanMove(GetPosition(), newPosition)) {
			// 회전
			MousePrsp();
			newPosition = GetPosition() + MouseMoveDirChange();
			// 방향 바꾼 후 다음 위치도 이동 가능한지 확인
			if (!level->CanMove(GetPosition(), newPosition))
			{ 
				// Todo: 게임오버 처리하기
				isStart = false;
				return;
			}
		}
		SetPosition(newPosition);
		timer.Reset();
		//- true → 그대로 이동
		//- false → 90도 회전
		//4. 회전한 새 방향으로 CanMove 재확인
		//- true → 이동
		//- false → 게임 오버
		//SetPosition(newPosition);
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

void Mouse::OnCollision(const std::shared_ptr<Actor>& other)
{
	
}

void Mouse::ArrowTileUpdateDirectionFromTile(std::shared_ptr<GameLevel> level)
{
	std::shared_ptr<ActiveTile> tiledir = level->FindActorAt<ActiveTile>(GetPosition());
	if (tiledir)
	{
		switch (tiledir->GetDir())
		{
		case TileDir::Right:
			direction = TileDir::Right;
			break;

		case TileDir::Left:
			direction = TileDir::Left;
			break;

		case TileDir::Up:
			direction = TileDir::Up;
			break;

		case TileDir::Down:
			direction = TileDir::Down;
			break;
		}
	}
}

