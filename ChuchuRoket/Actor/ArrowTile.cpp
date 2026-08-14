#include "ArrowTile.h"
#include <Input/Input.h>
#include <Level/GameLevel.h>
#include <Actor/ActiveTile.h>
#include <Windows.h>

using namespace Craft;

ArrowTile::ArrowTile(const Vector2& position)
	: Actor(L"⮞", position, Color::SKY)
	, startPosition(position)
{
	sortingOrder = 5;
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

bool ArrowTile::canStart(std::shared_ptr<GameLevel> gamelevel)
{
	// CanMove인지 아닌지 다시설정
	//std::shared_ptr<GameLevel> gamelevel = Cast<GameLevel>(GetOwner());
	// 화살표 카운트 내리기
	gamelevel->DecreaseArrowCount();
	//카운트 0이면 그만 생성
	if (gamelevel->GetRemainingArrowCount() <= 0) return false;
	return true;
}

bool ArrowTile::GetMoveKey(int keyCode)
{
	// 시프트 눌렷으면 대시
	if (Input::Get().GetKey(VK_SHIFT))
	{
		return Input::Get().GetKey(keyCode);
	}
	// 안눌렷으면  GetKeyDown
	return Input::Get().GetKeyDown(keyCode);
}

void ArrowTile::Tick(float deltaTime)
{
	super::Tick(deltaTime);

	// 이동 처리를 위해 GameLevel 객체 얻어오기
	// 다운캐스팅: 위험 -> 형변환 실패하면 null 반환
	std::shared_ptr<GameLevel> gamelevel = Cast<GameLevel>(GetOwner());
	if (gamelevel->GetisCanMove())
	{
		// wasd: 화살표 변경
		if (Input::Get().GetKeyDown('W')) 
			ArrowSelect(L"⮝", TileDir::Up);

		if (Input::Get().GetKeyDown('A'))
			ArrowSelect(L"⮜", TileDir::Left);

		if (Input::Get().GetKeyDown('S'))
			ArrowSelect(L"⮟", TileDir::Down);

		if (Input::Get().GetKeyDown('D'))
			ArrowSelect(L"⮞", TileDir::Right);

		// 방향키: 이동
		// shift 눌렀으면 GetKEy, 안눌럿으면 GetKeyDOwn
			if (GetMoveKey(VK_UP))
				SetPosition(ArrowMove(Vector2(0, -1), GetPosition(), gamelevel));

			if (GetMoveKey(VK_DOWN))
				SetPosition(ArrowMove(Vector2(0, 1), GetPosition(), gamelevel));

			if (GetMoveKey(VK_LEFT))
				SetPosition(ArrowMove(Vector2(-1, 0), GetPosition(), gamelevel));

			if (GetMoveKey(VK_RIGHT))
				SetPosition(ArrowMove(Vector2(1, 0), GetPosition(), gamelevel));
		

		// Enter: 확정 (초기 위치로 리셋, 방향키 다썻으면 destroy)
		if (Input::Get().GetKeyDown(VK_RETURN))
		{
			// 여기서 정지.
			//CanMove = false;
			//color = Color::PURPLE;
			std::shared_ptr<Level> level = GetOwner();

			if (level)
			{
				// 1. 현재 위치 + 방향으로 "영구 타일" 확정 생성.
				OutputDebugStringA("ActiveTile Spawned!\n");
				// 사운드 효과 재생
				Engine::Get().PlayOnShot("TileDown.wav");
				level->SpawnActor<ActiveTile>(image, GetPosition(), tileDir);

				// CanMove인지 아닌지 다시설정
				gamelevel->SetisCanMove(canStart(gamelevel));

				// 다음 화살표를 배치하기 위한 새 커서 스폰.
				//    초기 위치(시작 지점)에서 다시 시작.
				if (gamelevel->GetisCanMove()) {
					
					level->SpawnActor<ArrowTile>(startPosition);
				}
			}
			Destroy();
		}
	}
	
}