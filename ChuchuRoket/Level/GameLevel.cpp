#include "GameLevel.h"

#include <Actor/Wall.h>
#include <Actor/Goal.h>
#include <Actor/Mouse.h>
#include <Actor/Enemy.h>
#include <Actor/Ground.h>
#include <Actor/ArrowTile.h>
#include <Actor/ActiveTile.h>
#include <Actor/Cat.h>

#include <Game/Game.h>

#include <Render/Renderer.h>
#include <Input/Input.h>
#include <cassert>
#include <vector>

using namespace Craft;
void GameLevel::OnInitialized()
{
	Level::OnInitialized();
	Game& game = dynamic_cast<Game&>(Engine::Get());
	// Todo: 디버그 끝->눌러주세요
	// 파일 읽어서 맵 로드
	LoadMap("TileMap" + std::to_string(game.GetStageNum()) + ".txt");
	//LoadMap("TileMap4.txt");
	ProcessAddAndDestroyActors();
}


//Draw 이벤트 함수
void GameLevel::Draw()
{
	Level::Draw();
	Game& game = dynamic_cast<Game&>(Engine::Get());
	Renderer::Get().Submit(L"Stage " + std::to_wstring(game.GetStageNum()), Vector2(TextPosition.x + 2, 1));
	std::wstring text = L"남은 방향타일: " + std::to_wstring(remainingArrowCount);
	Renderer::Get().Submit(text, Vector2(TextPosition.x + 2, 3));
	Renderer::Get().Submit(L"쥐는 벽을 만나면 시계 방향으로 90도 회전합니다", Vector2(TextPosition.x + 2, 5));
	Renderer::Get().Submit(L"방향키: 타일 이동", Vector2(TextPosition.x + 2, 6));
	Renderer::Get().Submit(L"Shift + 방향키: 빠르게 타일 이동", Vector2(TextPosition.x + 2, 7));
	Renderer::Get().Submit(L"WASD: 타일 방향 바꾸기", Vector2(TextPosition.x + 2, 8));
	Renderer::Get().Submit(L"Enter: 타일 확정", Vector2(TextPosition.x + 2, 9));
}

void GameLevel::Tick(float deltaTime)
{
	Game& game = dynamic_cast<Game&>(Engine::Get());
	// 종료
	if (Input::Get().GetKeyDown(VK_ESCAPE))
	{
		Engine::Get().Quit();
	}
	// 게임 리셋(현재 스테이지 리셋)
	if (Input::Get().GetKeyDown('R'))
	{
		game.GoToGameLevel();
	}
	// 클리어 Level로 이동
	super::Tick(deltaTime);
	if (isGameClear)
	{
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
			SpawnActor<Mouse>(position);
			SpawnActor<Ground>(position);
			break;
		case 'R':
			SpawnActor<Ground>(position);
			SpawnActor<ArrowTile>(position);
			break;
		case 'G':
			SpawnActor<Goal>(position);
			targetScore++;
			break;
		case 'C':
			SpawnActor<Cat>(position);
			SpawnActor<Ground>(position);
			break;
		case 'M':
			SpawnActor<Ground>(position);
			SpawnActor<Enemy>(position);
			
			break;
		}

		++position.x;
	}
	TextPosition = position;

	delete[] buffer;
	buffer = nullptr;
	fclose(file);
	file = nullptr;
}
