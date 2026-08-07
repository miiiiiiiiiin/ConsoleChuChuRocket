#include "GameLevel.h"

#include <Actor/Box.h>
#include <Actor/Ground.h>
#include <Actor/Player.h>
#include <Actor/Target.h>
#include <Actor/Wall.h>

#include <iostream>
#include <cassert>
#include <cstdio>

using namespace Craft;
void GameLevel::OnInitialized()
{
	Level::OnInitialized();

	//파일 읽어서 맵 로드
	LoadMap("Map.txt");
}

void GameLevel::Draw()
{
	Level::Draw();
}

void GameLevel::LoadMap(const std::string& filename)
{
	//최종 경로 조립
	std::string path = std::string("../Assets/") + filename;

	//파일 열기
	FILE* file = nullptr;
	fopen_s(&file, path.c_str(), "rt");
	if (!file)
	{
		assert(false && "failed to open a sokoban stage file.");
		return;
	}

	//파일의 내용을 저장할 버퍼(데이터 저장공간) 확인
	//파일 길이 확인 -> 파일 위치 젤 뒤로 이동한담 해당 위치값 읽기
	fseek(file, 0, SEEK_END);
	long fileSize = ftell(file);

	//파일 젤 끝 위치를 구한담에 다시 처음으로 되돌리기
	rewind(file);

	//앞에서 구한 위치를 사용해서 버퍼 생성
	char* buffer = new char[fileSize] {};

	//데이터 읽기(파일 읽기
	size_t readSize = fread(buffer, sizeof(char), fileSize, file);

	// 어서트
	assert(readSize > 0 && "No data in the stage file.");

	//Todo: 읽은 데이터를 기반으로 로직 제작
	//1. 화면에 액터 그리기

	//문자열에 저장된 값을 접근할 때 사용할 인덱스
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
		case 'p':
			// 땅(플레이어 이동땜에 밀리니께), 플레이어 액터 생성
			SpawnActor<Ground>(position);
			SpawnActor<Player>(position);
			break;

			// 박스
		case 'b':
			// 땅(박스 이동땜에 밀리니께), 박스 액터 생성
			SpawnActor<Ground>(position);
			SpawnActor<Box>(position);
			break;

			// 목표 위치
		case 't':
			// 타겟 액터 생성
			SpawnActor<Target>(position);
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
