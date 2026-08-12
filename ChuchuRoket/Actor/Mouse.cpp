#include "Mouse.h"
#include "TileDir.h"

#include <Actor/Wall.h>
#include <Actor/ActiveTile.h>
#include <Actor/ArrowTile.h>
#include <Level/GameLevel.h>
#include <setTimer/Timer.h>
#include <Render/Renderer.h>

using namespace Craft;
Mouse::Mouse(const Craft::Vector2& position)
	: Actor(L"⯈", position, Color::BRIGHTWHITE),
	xPosition(GetPosition().x),
	yPosition(GetPosition().y), 
	timer(0.1f)

{
	sortingOrder = 5;
	//timer.SetTargetTime(0.5f);
}

void Mouse::Tick(float deltaTime)
{
	super::Tick(deltaTime);
	// Todo: 시작버튼 누르면 Tick 활성화되게 하기
	std::shared_ptr<GameLevel> level = Cast<GameLevel>(GetOwner());
	if (!level->GetisCanMove() && isStart)
	{
		//MouseMove(deltaTime);

		//1. 타이머 체크(아직 이동 타이밍 아니면 리턴)
		timer.Tick(deltaTime);
		if (!timer.isTimeOut())
		{
			return;
		}		
		//3. CanMove(현재방향) 확인
		Vector2 newPosition = GetPosition() + MouseMoveDirChange();

		// Todo: Mouse와 ActiveTile의 TileDir을 같도록 만드는 로직 고치기
		//2. 화살표 타일 확인 → 방향 갱신
		ArrowTileUpdateDirectionFromTile(level);

		// 다음위치 검사햇을때 이동불가면 90도 회전
		if (!level->CanMove(GetPosition(), newPosition)) {
			// 회전
			MousePrsp();
			newPosition = GetPosition() + MouseMoveDirChange();
			// 방향 바꾼 후 다음 위치도 이동 가능한지 확인
			if (!level->CanMove(GetPosition(), newPosition))
			{ 
				// Todo: 게임오버 처리하기.여기서 겜오버 창을 띄우던지해야됨
				isStart = false;
				return;
			}
		}
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
void Mouse::ArrowTileUpdateDirectionFromTile(std::shared_ptr<GameLevel> level)
{
	auto mousePos = GetPosition();
	auto tiledir = level->FindActorAt<ActiveTile>(mousePos);

	if (tiledir != nullptr)
	{
		direction = tiledir->GetDir();
	}
}

