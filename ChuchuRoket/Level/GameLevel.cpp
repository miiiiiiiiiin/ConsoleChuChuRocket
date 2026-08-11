#include "GameLevel.h"
#include <Actor/Wall.h>
#include <Actor/Goal.h>
#include <Actor/Mouse.h>
#include <Actor/Enemy.h>
#include <Actor/Ground.h>
#include <Actor/ArrowTile.h>
#include <Actor/ActiveTile.h>

#include <cassert>
#include <vector>

using namespace Craft;
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
		if (actor->IsTypeOf<ActiveTile>()) {
			tileMouseList.emplace_back(actor);
		}
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

	// 땅인 경우 가능. 그외 다 불가능
	for (std::shared_ptr<Actor> actor : actorList)
	{
		if (actor->GetPosition() == newPosition)
		{
			if (actor->IsTypeOf<Ground>())
				return true;
		}
		
	}

	return false;
}

void GameLevel::OnInitialized()
{
	Level::OnInitialized();

	// Todo: 파일 읽어서 맵 로드
	LoadMap("TileMap1.txt");

}

//Draw 이벤트 함수
void GameLevel::Draw()
{
	Level::Draw();

}

//맵 로드 함수
void GameLevel::LoadMap(const std::string& filename)
{
	//최종 경로 조립
	std::string path = std::string("../Map/") + filename;

	// 파일 열기
	FILE* file = nullptr;
	fopen_s(&file, path.c_str(), "rt"); // 텍스트모드 읽기

	//어디서부터 어디까지 읽을건지 구하기
	//fseek로 맨끝으로 가서 ftell로 몇번째인지 변수에넣고 rewind로 맨첨으로 ㄱㄱ
	fseek(file, 0, SEEK_END);
	long fileSize = ftell(file);
	rewind(file);

	// 사이즈만큼 file읽어서 버퍼에 넣기
	//버퍼 생성
	char* buffer = new char[fileSize];

	size_t readSize = fread(buffer, sizeof(char), fileSize, file);

	// 어서트
	assert(readSize > 0 && L"No data in the stage file.");

	// 읽은 데이터를 기반으로 로직 제작
	// 문자열 저장 값 접근 인덱스
	int index = 0;
	//액터 생성에 사용할 위치 값
	Vector2 position;
	while (true)
	{
		//종료 조건: 내용을 모두 읽었는지 파악
		if (index >= fileSize)
		{
			break;
		}
		// 이번에 확인할 문자 값 
		char mapCharacter = buffer[index++];

		// 인덱스 증가 처리
		// ++index;

		// 현재 문자가 개행 문자면 로직 건너뛰고 위치값 바꾸기
		if (mapCharacter == '\n')
		{
			++position.y;
			position.x = 0;
			continue;
		}

		// 읽은 문자 별로 처리
		switch (mapCharacter)
		{
			// 벽
		case '#':
			// 벽 액터 생성
			SpawnActor<Wall>(position);
			break;

			// 땅
		case '.':
			// 땅 액터 생성
			SpawnActor<Ground>(position);
			break;

			// 플레이어
		case 'P':
			// 땅(플레이어 이동땜에 깔림), 플레이어 액터 생성
			SpawnActor<Ground>(position);
			SpawnActor<Mouse>(position);
			break;

			// 화살표 타일
		case 'R':
			// 땅 (화살표에 깔림), 박스 액터 생성
			SpawnActor<Ground>(position);
			SpawnActor<ArrowTile>(position);
			break;

			// 목표 위치
		case 'G':
			// 타겟 액터 생성
			SpawnActor<Goal>(position);
			// 목표 스코어 증가 처리
			targetScore++;

			break;
		}

		// x 위치 업데이트
		++position.x;
	}


	//모두 사용한 버퍼 해제
	delete[] buffer;
	buffer = nullptr;

	//파일 닫기
	fclose(file);
	file = nullptr;
}