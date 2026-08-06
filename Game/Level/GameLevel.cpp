#include "GameLevel.h"
#include <iostream>
#include <cassert>
#include <cstdio>
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


	//모두 사용한 버퍼 해제
	delete[] buffer;
	buffer = nullptr;

	//파일 닫기
	fclose(file);


}
