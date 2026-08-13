#include "GameLevel.h"
#include <Actor/Wall.h>
#include <Actor/Goal.h>
#include <Actor/Mouse.h>
#include <Actor/Enemy.h>
#include <Actor/Ground.h>
#include <Actor/ArrowTile.h>
#include <Actor/ActiveTile.h>
#include <Render/Renderer.h>
#include <Game/Game.h>

#include <cassert>
#include <vector>

using namespace Craft;
void GameLevel::OnInitialized()
{
	Level::OnInitialized();
	Game& game = dynamic_cast<Game&>(Engine::Get());
	// Todo: 파일 읽어서 맵 로드
	LoadMap("TileMap" + std::to_string(game.GetStageNum()) + ".txt");
	ProcessAddAndDestroyActors();
}


//Draw 이벤트 함수
void GameLevel::Draw()
{
	Level::Draw();
	Game& game = dynamic_cast<Game&>(Engine::Get());
	std::wstring text = L"ArrowTile Count: " + std::to_wstring(remainingArrowCount);
	Renderer::Get().Submit(text, Vector2(23, 4));
	Renderer::Get().Submit(L"Stage" + std::to_wstring(game.GetStageNum()), Vector2(23, 5));
}

void GameLevel::Tick(float deltaTime)
{
	super::Tick(deltaTime);
	if (isGameClear)
	{
		Game& game = dynamic_cast<Game&>(Engine::Get());

		// 스테이지넘버 숫자 올리기
		game.StageNumCounting();

		// 클리어 화면 트리거 열기
		game.SetisClear(true);

		// 게임레벨 클리어 트리거 닫기
		isGameClear = false;

		// 클리어 화면으로 메인레벨 변경
		game.GoToClearLevel();
	}
}


bool GameLevel::CanMove(
	const Craft::Vector2& playerPosition,
	const Craft::Vector2& nextPosition)
{
	// 게임 클리어인 경우 처리 안함
	if (isGameClear)
	{
		return false;
	}
	// 이동 방향 구하기 -> 옆으로 이동하는 위치 구하기
	Vector2 dir = nextPosition - playerPosition;
	Vector2 newPosition = playerPosition + dir;

	// 액터리스트에서 ActiveTile, Mouse인 액터만 모으기
	std::vector<std::shared_ptr<Actor>> tileMouseList;
	for (std::shared_ptr<Actor> actor : actorList)
	{
		//if (actor->IsTypeOf<ActiveTile>()) {
		//	tileMouseList.emplace_back(actor);
		//}
		if (actor->IsTypeOf<Mouse>()) {
			tileMouseList.emplace_back(actor);
		}
	}

	// 다음 위치가 타일리스트인 경우 막기
	for (std::shared_ptr<Actor> actor : tileMouseList)
	{
		if (actor->GetPosition() == newPosition)
		{
			return false;
		}
	}

	//  타일 / 땅 밟기 가능
	for (std::shared_ptr<Actor> actor : actorList)
	{
		if (actor->GetPosition() == newPosition)
		{
			if (actor->IsTypeOf<ActiveTile>() ||
				actor->IsTypeOf<Ground>())
			{
				return true;
			}
		}
		
	}
	return false;
}

bool GameLevel::isSamePosition(const Craft::Vector2& playerPosition,
	const Craft::Vector2& nextPosition)
{
	// 타읽 밟으면 변경하기
	// 마우스의 direction ActiveTile의 tiledir 같게 만들기
	// 이동 방향 구하기 -> 옆으로 이동하는 위치 구하기
	Vector2 dir = nextPosition - playerPosition;
	Vector2 newPosition = playerPosition + dir;

	// 땅인 경우 가능. 그외 다 불가능
	for (std::shared_ptr<Actor> actor : actorList)
	{
		if (actor->GetPosition() == newPosition)
		{
			if (actor->IsTypeOf<ActiveTile>())
			{
				return true;
			}
		}

	}
	return false;
}


void GameLevel::LoadMap(const std::string& filename)
{
	std::string path = std::string("../Map/") + filename;

	FILE* file = nullptr;
	fopen_s(&file, path.c_str(), "rt");
	if (!file) return;

	fseek(file, 0, SEEK_END);
	long fileSize = ftell(file);
	rewind(file);

	char* buffer = new char[fileSize + 1];   // +1: 널 종단 위해 여유 확보
	size_t readSize = fread(buffer, sizeof(char), fileSize, file);
	buffer[readSize] = '\0';                 // 문자열로 다루기 위해 널 종단 처리

	assert(readSize > 0 && L"No data in the stage file.");

	int index = 0;

	// ---- 헤더 2줄 파싱: "Stage 1", "Arrow_Count: 1" ----
	for (int i = 0; i < 2; i++)
	{
		char lineBuffer[64] = {};
		int lineIndex = 0;

		// 개행 문자 나올 때까지 한 줄 복사.
		while (buffer[index] != '\n' && buffer[index] != '\0')
		{
			lineBuffer[lineIndex++] = buffer[index++];
		}
		lineBuffer[lineIndex] = '\0';
		++index;   // 개행 문자 건너뛰기.

		int count = 0;
		if (sscanf_s(lineBuffer, "Arrow_Count: %d", &count) == 1)
		{
			remainingArrowCount = count;
		}
		else if (sscanf_s(lineBuffer, "Stage %d", &count) == 1)
		{
			Game& game = dynamic_cast<Game&>(Engine::Get());
			game.SetStageNum(count);
		}
	}

	// ---- 여기서부터 실제 맵 파싱 (index는 헤더 2줄을 지나온 위치) ----
	Vector2 position;
	while (index < (int)readSize)
	{
		char mapCharacter = buffer[index++];

		if (mapCharacter == '\n')
		{
			++position.y;
			position.x = 0;
			continue;
		}

		switch (mapCharacter)
		{
		case '#':
			SpawnActor<Wall>(position);
			break;
		case '.':
			SpawnActor<Ground>(position);
			break;
		case 'P':
			SpawnActor<Ground>(position);
			SpawnActor<Mouse>(position);
			break;
		case 'R':
			SpawnActor<Ground>(position);
			SpawnActor<ArrowTile>(position);
			break;
		case 'G':
			SpawnActor<Goal>(position);
			targetScore++;
			break;
		}

		++position.x;
	}

	delete[] buffer;
	buffer = nullptr;
	fclose(file);
	file = nullptr;
}
