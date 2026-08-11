#include "ArrowTile.h"
#include <Input/Input.h>
#include <Windows.h>
#include <Level/GameLevel.h>
using namespace Craft;

ArrowTile::ArrowTile(const Vector2& position)
	: Actor(L"⮆", position, Color::YELLOW)
{
	sortingOrder = 3;
}

Vector2 ArrowTile::ArrowMove(
	Craft::Vector2 dir, 
	Craft::Vector2 nowPos, 
	std::shared_ptr<GameLevel> level)
{
		//이동하려는 위치값 만들기
		Vector2 newPosition = nowPos + dir;
	
		// 이동 가능 여부 확인
		if (level && level->CanMove(nowPos, newPosition))
		{
			return newPosition;
		}
	return nowPos;
}

void ArrowTile::ArrowSelect(std::wstring str, TileDir dir)
{
	// 이미지 변경, tileDir변경
	image = str;
	tileDir = dir;
}

void ArrowTile::Tick(float deltaTime)
{
	super::Tick(deltaTime);

	// 이동 처리를 위해 GameLevel 객체 얻어오기
	// 다운캐스팅: 위험 -> 형변환 실패하면 null 반환
	std::shared_ptr<GameLevel> level = Cast<GameLevel>(GetOwner());

	// wasd: 이동
	if (Input::Get().GetKeyDown('W')) 
		SetPosition(ArrowMove(Vector2(0, -1), GetPosition(), level));

	if (Input::Get().GetKeyDown('A'))
		SetPosition(ArrowMove(Vector2(-1, 0), GetPosition(), level));

	if (Input::Get().GetKeyDown('S'))
		SetPosition(ArrowMove(Vector2(0, 1), GetPosition(), level));

	if (Input::Get().GetKeyDown('D'))
		SetPosition(ArrowMove(Vector2(1, 0), GetPosition(), level));

	// 방향키: 화살표 변경
	if (Input::Get().GetKeyDown(VK_UP))
		ArrowSelect(L"⮝", Up);

	if (Input::Get().GetKeyDown(VK_DOWN))
		ArrowSelect(L"⮟", Up);

	if (Input::Get().GetKeyDown(VK_LEFT))
		ArrowSelect(L"⮜", Up);

	if (Input::Get().GetKeyDown(VK_RIGHT))
		ArrowSelect(L"⮞", Up);

	// r: 확정 (초기 위치로 리셋, 방향키 다썻으면 destroy)
	if (Input::Get().GetKeyDown('R'))
	{
		// 여기서 정지.
		// 새로운 객체를 생성한다.
	}
}